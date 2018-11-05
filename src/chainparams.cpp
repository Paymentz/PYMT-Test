// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 The PYMT developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x00000104b06b1cd499cced83d878ea92809cd84fc8d2b5523e19d2d16c99f549"))
    (150, uint256("0x00000929b295ce073f4dd9a146893b3e33dafaae7ed36d5bb2ad3159e5ce15df"))
    (200, uint256("0x00000087186aee20b63303710171cf299adbef3d373581b0510873e2ab709b0b"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1539647004, // * UNIX timestamp of last checkpoint block
    202,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x00000715ca10a76a9ed27f745ee5133934b8b30bb07d47948827b9fa16b0eb87"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1538275048,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x300e9ef306fa2262674d6251dd4c0177d24dbadb9662846a76164172beec45ff"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1538265600,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
         pchMessageStart[0] = 0xf4;
         pchMessageStart[1] = 0xcb;
         pchMessageStart[2] = 0xbd;
         pchMessageStart[3] = 0xe2;
        vAlertPubKey = ParseHex("04a36a426b812a83776c6edead336d19af5d2ca3a548697acb3c6f201ba51b44758619b281f1096b65e643b4d996b90afe4a9e08dd6e54600d5c81897a1ec3a453");
        nDefaultPort = 37006;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // PYMT starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 864000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // PYMT: 1 day
        nTargetSpacing = 1 * 60;  // PYMT: 1 minute
        nLastPOWBlock = 300;
        nMaturity = 90;
        nMasternodeCountDrift = 10;
        nMasternodeCollateralLimit = 1000;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 20000000 * COIN;

        const char* pszTimestamp = "The Times - How to be a sex worker: Brighton University advice for freshers";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 4194596 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 10 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04792b5475e8199e0798d70f18bcff945c42e0abff135467fe61dc7491579a2c7e1fc8754def07bc43fe15138ec01c8124f10b4829397ca3a3c9cfba06ab394f7d") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1538265600;
        genesis.nBits = 0x1e0fffff;
        genesis.nNonce = 961023;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000104b06b1cd499cced83d878ea92809cd84fc8d2b5523e19d2d16c99f549"));
        assert(genesis.hashMerkleRoot == uint256("0x23b5bae265343a0fe0ce6fe1c1358fb89c9fcb0a885f3eda3e8a2c79e7f486b1"));

        vSeeds.push_back(CDNSSeedData("54.37.205.229", "54.37.205.229"));
        vSeeds.push_back(CDNSSeedData("144.217.161.46", "144.217.161.46"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 45);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 31);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 60);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04050adbaaab7ab704cf78367374d0661cb0e82050838075c13e6e53deb324d5466243a1cd9c54bd2abc43605aeaa48032fa6520bb7c8d6a20b9f88394134dc847";
        strObfuscationPoolDummyAddress = "KDjbvBPN5US5tZeFVeGWicahobjTZG9yLy";
        nStartMasternodePayments = 1539648000;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xb1;
        pchMessageStart[1] = 0xe2;
        pchMessageStart[2] = 0xf4;
        pchMessageStart[3] = 0xc3;
        vAlertPubKey = ParseHex("04792b5475e8199e0798d70f18bcff945c42e0abff135467fe61dc7491579a2c7e1fc8754def07bc43fe15138ec01c8124f10b4829397ca3a3c9cfba06ab394f7d");
        nDefaultPort = 37005;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // PYMT: 1 day
        nTargetSpacing = 1 * 60;  // PYMT: 1 minute
        nLastPOWBlock = 150;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nMasternodeCollateralLimit = 1000;
        nModifierUpdateBlock = 1; // PYMT uses version 2 blocks
        nMaxMoneyOut = 200000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1538275048;
        genesis.nNonce = 918077;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000715ca10a76a9ed27f745ee5133934b8b30bb07d47948827b9fa16b0eb87"));
        assert(genesis.hashMerkleRoot == uint256("0x23b5bae265343a0fe0ce6fe1c1358fb89c9fcb0a885f3eda3e8a2c79e7f486b1"));


        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 108);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 90);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04050adbaaab7ab704cf78367374d0661cb0e82050838075c13e6e53deb324d5466243a1cd9c54bd2abc43605aeaa48032fa6520bb7c8d6a20b9f88394134dc847";
        strObfuscationPoolDummyAddress = "k7t1mjRDgu5DDRKrTMf5iFBr2wZzu8os9w";
        nStartMasternodePayments = 1539648000;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa3;
        pchMessageStart[1] = 0xf1;
        pchMessageStart[2] = 0xd4;
        pchMessageStart[3] = 0xf3;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // PYMT: 1 day
        nTargetSpacing = 1 * 60;        // PYMT: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nDefaultPort = 38006;
        genesis.nTime = 1538265600;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 2;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x300e9ef306fa2262674d6251dd4c0177d24dbadb9662846a76164172beec45ff"));
        assert(genesis.hashMerkleRoot == uint256("0x23b5bae265343a0fe0ce6fe1c1358fb89c9fcb0a885f3eda3e8a2c79e7f486b1"));


        vFixedSeeds.clear(); //! regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 38005;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
