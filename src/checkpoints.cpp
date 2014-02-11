// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 Elephantcoin Developers
// Copyright (c) 2014 HotDogCoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

	// no checkpoint now, can be added in later releases
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
(0,    uint256("0x4e24e7e9887b54346560fa1f23e02d4eb5cc24a709b697ca8bd03315aa1114d1"))
//(1,    uint256("0x00000518429c88e6d490d1e449e027297c6baa2898fbda49254f16259fe2d2d1"))
//(10,   uint256("0x000001df66b0c0c1f96c467ba00b216b96118f30626f55608eb3217012f69e5e"))
//(20,   uint256("0x00000a4922ce062025b96733d190213cf5f7948aa2b799901332a0933278f38b"))
//(30,   uint256("0x00000e23ae92d5c2932922c52536b50c2ed8017c8d8e053459e40e6760f7a1e2"))
//(50,   uint256("0x0000076072ad2512c730d9ac9fb58f6f76b5cea62ed943c24b1dbb5bd09b40c5"))
//(80,   uint256("0x00000f7fc951d8a388d5323d0046479167e97823a1cb5c385ad201adc4074bd1"))
//(100,  uint256("0x00000b9faaeed91b48b2e5b4b13d376aca7bab0624d24821bb785b092e20fd29"))

;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
//return true;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;

        return mapCheckpoints.rbegin()->first;
//return 0;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
           return t->second;
//return NULL;
        }
        return NULL;
    }
}
