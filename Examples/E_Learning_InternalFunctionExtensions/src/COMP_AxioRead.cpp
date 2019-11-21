#include "COMP_AxioRead.hpp"

#include "rapidjson/error/en.h"
#include "rapidjson/schema.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/prettywriter.h"
#include <fstream>

using namespace rapidjson;

namespace LIB_AxioRead
{

void COMP_AxioRead::Initialize()
{
// subscribe events from the event system (Nm) here
}

void COMP_AxioRead::SubscribeServices()
{
	// subscribe the service for acyclic communication
	this->pAcyclicCommunicationService = ServiceManager::GetService<IAcyclicCommunicationService>();
}

void COMP_AxioRead::LoadSettings(const String& settingsPath) // use settings path configured in acf.config
{
	// check file access
	if((pConfigFile = fopen(settingsPath, "r")) == NULL) // try to open file for reading ("r")
	{
		Log::Error("PDI configuration file could not be loaded");
	}
	else
	{
		Log::Info("PDI configuration file successfully loaded");
	}

}

void COMP_AxioRead::SetupSettings()
{
	// --------------------------------------------------------------------------------------------------------
	// Analyze the schema file .schema.json
	// --------------------------------------------------------------------------------------------------------

	// check access to schema file
	FILE* pSchemaFile;
	if( (pSchemaFile = fopen("/opt/plcnext/projects/Components/AxioReadConfig.schema.json", "r")) == NULL)
	{
		Log::Error("The JSON schema could not be loaded");
	}
	else
	{
		Log::Info("The JSON schema was loaded successfully");
	}

	// read schema file stream
	char schemaBuffer[65536];
	FileReadStream schemaStream(pSchemaFile, schemaBuffer, sizeof(schemaBuffer));

	// create document with schema file contents
	Document dSchema;
	dSchema.ParseStream(schemaStream);

	// close the schema file
	fclose(pSchemaFile);

	// compile the document to SchemaDocument
	SchemaDocument sdSchema(dSchema);

	// --------------------------------------------------------------------------------------------------------
	// Handle .json configuration file
	// --------------------------------------------------------------------------------------------------------

	// read json file stream
	char readBuffer[65536];
	FileReadStream jsonStream(pConfigFile, readBuffer, sizeof(readBuffer));

	// --------------------------------------------------------------------------------------------------------
	// Validation
	// --------------------------------------------------------------------------------------------------------

	Reader reader;
	SchemaValidator validator(sdSchema);

	// Use reader to parse the JSON in stdin, and forward SAX events to validator
	if (!reader.Parse(jsonStream, validator) && reader.GetParseErrorCode() != kParseErrorTermination)
	{
		Log::Error("Input is not a valid JSON");
		Log::Error("Error: {0}, {1}", static_cast<unsigned>(reader.GetErrorOffset()), GetParseError_En(reader.GetParseErrorCode()));
	}

	if (!validator.IsValid())
	{
		Log::Error("JSON file contents are invalid");
		StringBuffer sb;
		validator.GetInvalidSchemaPointer().StringifyUriFragment(sb);
		Log::Error("Invalid schema: {0}", sb.GetString());
		Log::Error("Invalid keyword: {0}", validator.GetInvalidSchemaKeyword());
		sb.Clear();
		validator.GetInvalidDocumentPointer().StringifyUriFragment(sb);
		Log::Error("Invalid document: {0}", sb.GetString());

		// Detailed violation report is available as a JSON value
		sb.Clear();
		PrettyWriter<StringBuffer> w(sb);
		validator.GetError().Accept(w);
		Log::Error("Error report: {0}", sb.GetString());
	}
	else if (validator.IsValid())
	{
		Log::Info("JSON file contents are valid");
		Document dJson;
		dJson.Parse(std::stringstream(readBuffer).str().c_str());

		Value::MemberIterator configIterator = dJson.FindMember( "Configurations" );
		const Value& configs = dJson[ "Configurations" ];

		assert(configs.IsArray());
		for (Value::ConstValueIterator i1 = configs.Begin(); i1 != configs.End(); ++i1)
		{
			const Value& config = *i1;
			assert(config.IsObject()); // each configuration is an object

			for (Value::ConstMemberIterator i2 = config.MemberBegin(); i2 != config.MemberEnd(); ++i2)
			{
				if (n <= 100) // prevent overflow
				{
					// fill array of struct
					if (string(i2->name.GetString()) == "Index")
					{
						arConfigs[n].Index = uint16(i2->value.GetInt());
						Log::Info("Index[{0}] = {1}", n, arConfigs[n].Index);
					}
					else if (string(i2->name.GetString()) == "Subindex")
					{
						arConfigs[n].Subindex = uint8(i2->value.GetInt());
						Log::Info("Subindex[{0}] = {1}", n, uint16(arConfigs[n].Subindex));
					}
					else if (string(i2->name.GetString()) == "DisplayAsText")
					{
						arConfigs[n].DisplayAsText = bool(i2->value.GetBool());
						Log::Info("DisplayAsText[{0}] = {1}", n, arConfigs[n].DisplayAsText);
					}
				}
				else
				{
					Log::Warning("Max. number of 100 data sets reached in the JSON configuration file");
				}
			}
			n = n + 1;
		}
	}
}

void COMP_AxioRead::PublishServices()
{
	// publish the services of this component here
}

void COMP_AxioRead::LoadConfig()
{
	WorkerThreadInstance.Start();
	Log::Info("Thread of COMP_AxioRead is started");
}

void COMP_AxioRead::SetupConfig()
{
	// never remove next line
	MetaComponentBase::SetupConfig();

	// setup project config here
}

void COMP_AxioRead::ResetConfig()
{
	// never remove next line
	MetaComponentBase::ResetConfig();

	// implement this inverse to SetupConfig() and LoadConfig()
}

void COMP_AxioRead::Dispose()
{
	WorkerThreadInstance.Stop();
	Log::Info("COMP_AxioRead and Thread stopped");
}

void COMP_AxioRead::PowerDown()
{
	// implement this only if data must be retained even on power down event
}

void COMP_AxioRead::WorkerThreadBody(void)
{
	// cyclic executed code

	// -------------------------------------------------------------------------
	// Read input data (switch module status)
	// --------------------------------------------------------------------------

	paramProcessData.Slot = 1; // read data from the first module
	paramProcessData.Subslot = 0; // subslot is always 0
	paramProcessData.Index = 37; // process data access via index 37
	paramProcessData.Subindex = 0; // subindex for process data access is 0

	std::vector<uint8> processData; // result of the read process
	PdiResult resultProcessDataRead = this->pAcyclicCommunicationService->PdiRead(paramProcessData, processData);
    //Log::Info("Process data: {0:#x}", processData[0]); //write data as hex value

	// -------------------------------------------------------
	// Use switch status to read the PDI data configured in the JSON file
	// -------------------------------------------------------

	if (switchFlag != processData[0]) // if the status of the input data changed, write PDI data in log file
	{

		if ((processData[0] != 0) && (processData[0]< 63)) // but first check that status is not zero and less than 63
		{
			param.Slot = processData[0]; // switch state = module to select
			param.Subslot = 0;	// subslot is always set to "0"

			for (int i1 = 0; i1 < n; i1++) // go through each json configuration an read the respective data
			{
				param.Index = arConfigs[i1].Index;
				param.Subindex = arConfigs[i1].Subindex;

				std::vector<uint8> data; // final data
				PdiResult result = this->pAcyclicCommunicationService->PdiRead(param, data);

				if (arConfigs[i1].DisplayAsText) // if in the JSON "DisplayAsText" = "true" print data in ASCI format
				{
					int m = 0;
					string dataText;

					for (auto i2 = data.begin(); i2 != data.end(); i2++)
					{
						if (data[m] != 0)
						{
							dataText += data[m];
						}
						else
						{
							Log::Info("PDI data {0} : {1}", i1, dataText);
							break;
						}
						m = m + 1;
					}
				}
				else // else print them as hex number in the log file
				{
					int m = 0;
					for (auto i2 = data.begin(); i2 != data.end(); i2++)
					{
						Log::Info("PDI data {0} : {1:#x}", i1, data[m]);
						m = m + 1;
					}
				}
				// Write whether this data set is valid or not
				Log::Info("PDI info {0} - ErrorCode : {1:#x} , AddInfo : {2:#x}", i1, result.ErrorCode, result.AddInfo);
			}
		}
		else
		{
			Log::Info("PDI Read: Invalid module access");
		}
	}
	switchFlag = processData[0];
}

} // end of namespace LIB_AxioRead
