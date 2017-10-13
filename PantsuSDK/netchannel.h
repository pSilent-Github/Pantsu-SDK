#include "top.h"
class INetChannel
{
public:
	char pad_0000[24]; //0x0000
	int m_nOutSequenceNr; //0x0018
	int m_nInSequenceNr; //0x001C
	int m_nOutSequenceNrAck; //0x0020
	int m_nOutReliableState; //0x0024
	int m_nInReliableState; //0x0028
	int m_nChokedPackets; //0x002C
	char pad_0030[108]; //0x0030
	int m_Socket; //0x009C
	int m_StreamSocket; //0x00A0
	int m_MaxReliablePayloadSize; //0x00A4
	char pad_00A8[100]; //0x00A8
	float last_received; //0x010C
	float connect_time; //0x0110
	char pad_0114[4]; //0x0114
	int m_Rate; //0x0118
	char pad_011C[4]; //0x011C
	float m_fClearTime; //0x0120
	char pad_0124[16688]; //0x0124
	char m_Name[32]; //0x4254
	unsigned int m_ChallengeNr; //0x4274
	float m_flTimeout; //0x4278
	char pad_427C[32]; //0x427C
	float m_flInterpolationAmount; //0x429C
	float m_flRemoteFrameTime; //0x42A0
	float m_flRemoteFrameTimeStdDeviation; //0x42A4
	int m_nMaxRoutablePayloadSize; //0x42A8
	int m_nSplitPacketSequence; //0x42AC
	char pad_42B0[40]; //0x42B0
	bool m_bIsValveDS; //0x42D8
	char pad_42D9[65]; //0x42D9
}; //Size: 0x431A