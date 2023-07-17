#include "define.h"


class Screen{
  public:
    spi_inst_t *spi;

    void Init();
    void Reset();
    void Clear();

    static void SendCommand(BYTE);
    static void SendData(BYTE);
}
