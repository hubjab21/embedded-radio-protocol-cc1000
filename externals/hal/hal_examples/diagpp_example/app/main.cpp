#include "hal.hpp"

using namespace halfred;

static uint32_t timeProvider()
{
	return OS_GetSystemTime();
}

DiagChannel log(1, IO_STD, timeProvider);

int main()
{
	IODEV_Init(IO_STD);
	IODEV_EnableWrite(IO_STD);

	log.activate();
	DIAG0(log << header("LEVEL0") << "Message" << endl);
	DIAG1(log << header("LEVEL1") << "Message" << endl);
	DIAG2(log << header("LEVEL2") << "Message" << endl);
	DIAG3(log << header("LEVEL3") << "Message" << endl);
	DIAG4(log << header("LEVEL4") << "Message" << endl);
	log << header("INT TEST") << 12345678 << endl;
	log << header("UINT TEST") << 0xffffffff << endl;
	log << header("HEX TEST") << hex << 0xdeadbeef << endl;
	log << header("FLOAT TEST") << (float)1234.5678 << endl;

	IODEV_Deinit(IO_STD);

	return 0;
}
