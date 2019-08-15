// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
	uint8_t addr[16];
	uint16_t port;
};

#include "chainparamsseeds.h"
//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
	// It will only connect to one or two seed nodes because once it connects,
	// it will get a pile of addresses with newer timestamps.
	// Seed nodes are given a random "last seen time" of between one and two
	// weeks ago.
	const int64_t nOneWeek = 7 * 24 * 60 * 60;
	for (unsigned int k = 0; k < count; ++k)
	{
		struct in_addr ip;
		unsigned int i = data[k], t;

		// -- convert to big endian
		t = (i & 0x000000ff) << 24u
			| (i & 0x0000ff00) << 8u
			| (i & 0x00ff0000) >> 8u
			| (i & 0xff000000) >> 24u;

		memcpy(&ip, &t, sizeof(ip));

		CAddress addr(CService(ip, port));
		addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
		vSeedsOut.push_back(addr);
	}
}

class CMainParams : public CChainParams {
public:
	CMainParams() {
		// The message start string is designed to be unlikely to occur in normal data.
		// The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		// a large 4-byte int at any alignment.
		pchMessageStart[0] = 0x9d;
		pchMessageStart[1] = 0x2a;
		pchMessageStart[2] = 0x22;
		pchMessageStart[3] = 0x5b;
		vAlertPubKey = ParseHex("042d9aad81889a23c46bb4f15e3b605400d784ffb486c51f32a8e736f9a6276b96c24f2137e7046b4c288be41da0476b37607b21440389dac180b47558343ab91c");
		nDefaultPort = 41426;
		nRPCPort = 41427;
		bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

		// Build the genesis block. Note that the output of the genesis coinbase cannot
		// be spent as it did not originally exist in the database.
		
		
		const char* pszTimestamp = "start FDEL coin on Thursday, 15 August 2019, 11:03:22";
		std::vector<CTxIn> vin;
		vin.resize(1);
		vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
		std::vector<CTxOut> vout;
		vout.resize(1);
		vout[0].SetEmpty();
		CTransaction txNew(1, 1565867002, vin, vout, 0);
		genesis.vtx.push_back(txNew);
		genesis.hashPrevBlock = 0;
		genesis.hashMerkleRoot = genesis.BuildMerkleTree();
		genesis.nVersion = 1;
		genesis.nTime = 1565867002;
		genesis.nBits = 0x1e0ffff0;
		genesis.nNonce = 440309;

		hashGenesisBlock = genesis.GetHash();
  
        LogPrintf("Display genesis hash so we can input it below %s\n", hashGenesisBlock.ToString().c_str());
	    LogPrintf("Display merkle root so we can input it below %s\n", genesis.hashMerkleRoot.ToString().c_str());
        LogPrintf("Display nonce so we can input it below %s\n", genesis.nNonce);
        LogPrintf("Display time so we can input it below %s\n", genesis.nTime);

		assert(genesis.hashMerkleRoot == uint256("0xcca1440d8e9d99a21438511cec9930f335d3b1e53f13e64f268204ad6d002cf3"));
		assert(hashGenesisBlock == uint256("0x1ac86b2e70b7b86379e22b01bd871cfd3f059a470ce4a346480401d8fbad36d2"));

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 35);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 95);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 137);
		base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 135);
		base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

		vSeeds.push_back(CDNSSeedData("0", "80.211.187.163"));
		vSeeds.push_back(CDNSSeedData("1", "80.211.10.160"));
//		vSeeds.push_back(CDNSSeedData("2", "80.211.10.160"));
		convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

		nPoolMaxTransactions = 3;
		strDarksendPoolDummyAddress = "fFoQDUrp63QWqFhjEr3Fmc4ubHRhyzjKUC";
		nLastPOWBlock = 600000;
		nPOSStartBlock = 20;
	}


	virtual const CBlock& GenesisBlock() const { return genesis; }
	virtual Network NetworkID() const { return CChainParams::MAIN; }

	virtual const vector<CAddress>& FixedSeeds() const {
		return vFixedSeeds;
	}
protected:
	CBlock genesis;
	vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
	CTestNetParams() {
		// The message start string is designed to be unlikely to occur in normal data.
		// The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		// a large 4-byte int at any alignment.
		pchMessageStart[0] = 0x1c;
		pchMessageStart[1] = 0x8e;
		pchMessageStart[2] = 0xa7;
		pchMessageStart[3] = 0x1d;
		bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
		vAlertPubKey = ParseHex("042d9aad81889a23c46bb4f15e3b605400d784ffb486c51f32a8e736f9a6276b96c24f2137e7046b4c288be41da0476b37607b21440389dac180b47558343ab91c");
		nDefaultPort = 31407;
		nRPCPort = 31408;
		strDataDir = "testnet";

		// Modify the testnet genesis block so the timestamp is valid for a later start.
		genesis.nBits = 0x1e0ffff0;
		genesis.nNonce = 216893;
		genesis.nTime    = 1565867003;

        hashGenesisBlock = genesis.GetHash();

        LogPrintf("Display testNet genesis hash so we can input it below %s\n", hashGenesisBlock.ToString().c_str());

		assert(hashGenesisBlock == uint256("0x0efae91d5e242144c1f2007c79d66a96844b374aeaf1024f940955e0e6343bf9"));

		vFixedSeeds.clear();
		vSeeds.clear();

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 127);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);
		base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 40);
		base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

		convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

		nLastPOWBlock = 0x7fffffff;
	}
	virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
	return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
	switch (network) {
	case CChainParams::MAIN:
		pCurrentParams = &mainParams;
		break;
	case CChainParams::TESTNET:
		pCurrentParams = &testNetParams;
		break;
	default:
		assert(false && "Unimplemented network");
		return;
	}
}

bool SelectParamsFromCommandLine() {

	bool fTestNet = GetBoolArg("-testnet", false);

	if (fTestNet) {
		SelectParams(CChainParams::TESTNET);
	}
	else {
		SelectParams(CChainParams::MAIN);
	}
	return true;
}