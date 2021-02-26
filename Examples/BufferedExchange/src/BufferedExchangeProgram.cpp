#include <BufferedExchangeProgram.hpp>
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Core/ByteConverter.hpp"

namespace BufferedExchange
{

    void BufferedExchangeProgram::Execute()
    {
        //implement program
        if (count % 1000 == 0)
        {
            log.Info("---------------- Execute: {0} ", count);
        }
        count++;

        //Watch out blocking!
        if (bufferedExchangeComponent.wT.SetData(count))
        {
            log.Warning("-------------- Instance:{1} DataLost: {0} ", count, this->GetFullName());
        }

        if (bufferedExchangeComponent.wS.SetData(count_d))
        {
            log.Warning("-------------- Instance:{1} DataLost: {0} ", count_d, this->GetFullName());
        }

        count_d++;
        if (bufferedExchangeComponent.wD.SetData(count_d + count))
        {
            log.Warning("-------------- Instance:{1} DataLost: {0} ", count_d + count, this->GetFullName());
        }
    }

} // end of namespace BufferedExchange
