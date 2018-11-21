#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeSystem.h"
#include "CppDataTypeTest/CppDataTypeTestProgram.hpp"
#include "CppDataTypeTest/CppDataTypeTestProgram.hpp"
#include "CppDataTypeTestLibrary.hpp"

namespace CppDataTypeTest 
{

using namespace Arp::Plc::Commons::Meta;

    void CppDataTypeTestLibrary::InitializeTypeDomain()
    {
        this->typeDomain.AddTypeDefinitions
        (
            // Begin TypeDefinitions
            {
                {    // TypeDefinition: ::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes
                    DataType::Struct, CTN<::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes>(), sizeof(::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes), alignof(::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "outInt8",offsetof(::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes, outInt8), DataType::Int8, "", sizeof(int8), alignof(int8), { }, StandardAttribute::None },
                        { "outUint8",offsetof(::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes, outUint8), DataType::UInt8, "", sizeof(uint8), alignof(uint8), { }, StandardAttribute::None },
                        { "outInt16",offsetof(::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes, outInt16), DataType::Int16, "", sizeof(int16), alignof(int16), { }, StandardAttribute::None },
                        { "outUint16",offsetof(::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes, outUint16), DataType::UInt16, "", sizeof(uint16), alignof(uint16), { }, StandardAttribute::None },
                        { "outInt32",offsetof(::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes, outInt32), DataType::Int32, "", sizeof(int32), alignof(int32), { }, StandardAttribute::None },
                        { "outUint32",offsetof(::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes, outUint32), DataType::UInt32, "", sizeof(uint32), alignof(uint32), { }, StandardAttribute::None },
                        { "outInt64",offsetof(::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes, outInt64), DataType::Int64, "", sizeof(int64), alignof(int64), { }, StandardAttribute::None },
                        { "outUint64",offsetof(::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes, outUint64), DataType::UInt64, "", sizeof(uint64), alignof(uint64), { }, StandardAttribute::None },
                        { "outByte",offsetof(::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes, outByte), DataType::UInt8, "", sizeof(uint8), alignof(uint8), { }, StandardAttribute::None },
                        { "outWord",offsetof(::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes, outWord), DataType::UInt16, "", sizeof(uint16), alignof(uint16), { }, StandardAttribute::None },
                        { "outDword",offsetof(::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes, outDword), DataType::UInt32, "", sizeof(uint32), alignof(uint32), { }, StandardAttribute::None },
                        { "outLword",offsetof(::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes, outLword), DataType::UInt64, "", sizeof(uint64), alignof(uint64), { }, StandardAttribute::None },
                        { "outFloat32",offsetof(::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes, outFloat32), DataType::Float32, "", sizeof(float32), alignof(float32), { }, StandardAttribute::None },
                        { "outFloat64",offsetof(::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes, outFloat64), DataType::Float64, "", sizeof(float64), alignof(float64), { }, StandardAttribute::None },
                    }
                },

                {    // ProgramDefinition: ::CppDataTypeTest::CppDataTypeTestProgram
                    DataType::Program, CTN<::CppDataTypeTest::CppDataTypeTestProgram>(), sizeof(::CppDataTypeTest::CppDataTypeTestProgram), alignof(::CppDataTypeTest::CppDataTypeTestProgram), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "outBoolean",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outBoolean), DataType::Boolean, "", sizeof(boolean), alignof(boolean), { }, StandardAttribute::Output },
                        { "outInt8",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outInt8), DataType::Int8, "", sizeof(int8), alignof(int8), { }, StandardAttribute::Output },
                        { "outUint8",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outUint8), DataType::UInt8, "", sizeof(uint8), alignof(uint8), { }, StandardAttribute::Output },
                        { "outInt16",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outInt16), DataType::Int16, "", sizeof(int16), alignof(int16), { }, StandardAttribute::Output },
                        { "outUint16",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outUint16), DataType::UInt16, "", sizeof(uint16), alignof(uint16), { }, StandardAttribute::Output },
                        { "outInt32",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outInt32), DataType::Int32, "", sizeof(int32), alignof(int32), { }, StandardAttribute::Output },
                        { "outUint32",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outUint32), DataType::UInt32, "", sizeof(uint32), alignof(uint32), { }, StandardAttribute::Output },
                        { "outInt64",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outInt64), DataType::Int64, "", sizeof(int64), alignof(int64), { }, StandardAttribute::Output },
                        { "outUint64",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outUint64), DataType::UInt64, "", sizeof(uint64), alignof(uint64), { }, StandardAttribute::Output },
                        { "outByte",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outByte), DataType::UInt8, "", sizeof(uint8), alignof(uint8), { }, StandardAttribute::Output },
                        { "outWord",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outWord), DataType::UInt16, "", sizeof(uint16), alignof(uint16), { }, StandardAttribute::Output },
                        { "outDword",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outDword), DataType::UInt32, "", sizeof(uint32), alignof(uint32), { }, StandardAttribute::Output },
                        { "outLword",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outLword), DataType::UInt64, "", sizeof(uint64), alignof(uint64), { }, StandardAttribute::Output },
                        { "outFloat32",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outFloat32), DataType::Float32, "", sizeof(float32), alignof(float32), { }, StandardAttribute::Output },
                        { "outFloat64",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outFloat64), DataType::Float64, "", sizeof(float64), alignof(float64), { }, StandardAttribute::Output },
                        { "outStruct",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outStruct), DataType::Struct, CTN<::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes>(), sizeof(::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes), alignof(::CppDataTypeTest::CppDataTypeTestProgram::s_alltypes), { }, StandardAttribute::Output },
                        { "outarrayBoolean",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outarrayBoolean), DataType::Boolean | DataType::Array, "", sizeof(boolean), alignof(boolean), { 10 }, StandardAttribute::Output },
                        { "outarrayInt8",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outarrayInt8), DataType::Int8 | DataType::Array, "", sizeof(int8), alignof(int8), { 10 }, StandardAttribute::Output },
                        { "outarrayUint8",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outarrayUint8), DataType::UInt8 | DataType::Array, "", sizeof(uint8), alignof(uint8), { 10 }, StandardAttribute::Output },
                        { "outarrayInt16",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outarrayInt16), DataType::Int16 | DataType::Array, "", sizeof(int16), alignof(int16), { 10 }, StandardAttribute::Output },
                        { "outarrayUint16",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outarrayUint16), DataType::UInt16 | DataType::Array, "", sizeof(uint16), alignof(uint16), { 10 }, StandardAttribute::Output },
                        { "outarrayInt32",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outarrayInt32), DataType::Int32 | DataType::Array, "", sizeof(int32), alignof(int32), { 10 }, StandardAttribute::Output },
                        { "outarrayUint32",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outarrayUint32), DataType::UInt32 | DataType::Array, "", sizeof(uint32), alignof(uint32), { 10 }, StandardAttribute::Output },
                        { "outarrayInt64",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outarrayInt64), DataType::Int64 | DataType::Array, "", sizeof(int64), alignof(int64), { 10 }, StandardAttribute::Output },
                        { "outarrayUint64",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outarrayUint64), DataType::UInt64 | DataType::Array, "", sizeof(uint64), alignof(uint64), { 10 }, StandardAttribute::Output },
                        { "outarrayByte",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outarrayByte), DataType::UInt8 | DataType::Array, "", sizeof(uint8), alignof(uint8), { 10 }, StandardAttribute::Output },
                        { "outarrayWord",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outarrayWord), DataType::UInt16 | DataType::Array, "", sizeof(uint16), alignof(uint16), { 10 }, StandardAttribute::Output },
                        { "outarrayDword",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outarrayDword), DataType::UInt32 | DataType::Array, "", sizeof(uint32), alignof(uint32), { 10 }, StandardAttribute::Output },
                        { "outarrayLword",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outarrayLword), DataType::UInt64 | DataType::Array, "", sizeof(uint64), alignof(uint64), { 10 }, StandardAttribute::Output },
                        { "outarrayFloat32",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outarrayFloat32), DataType::Float32 | DataType::Array, "", sizeof(float32), alignof(float32), { 10 }, StandardAttribute::Output },
                        { "outarrayFloat64",offsetof(::CppDataTypeTest::CppDataTypeTestProgram, outarrayFloat64), DataType::Float64 | DataType::Array, "", sizeof(float64), alignof(float64), { 10 }, StandardAttribute::Output },
                    }
                },

            }
            // End TypeDefinitions
        );
    }

} // end of namespace CppDataTypeTest

