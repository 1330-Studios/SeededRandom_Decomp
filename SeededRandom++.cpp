#include <cstdio>
#include <Windows.h>
#include <string>
#include <vector>

#include "SeededRandom.h"

const char** shuffle_seeded(SeededRandom* seeded_random, const char** list, const int length, long long seed) {
    seeded_random->currentSeed = seed;

    int idx_2 = length - 1;

    while (true) {
	    const double random_double = seeded_random->NextDouble();
	    const int idx = static_cast<int>(random_double * length);

	    const auto temp = list[idx_2];
        list[idx_2] = list[idx];
        list[idx] = temp;
        
        if (--idx_2 < 0)
            return list;
    }
}

int main() {
    std::vector instaMonkeys_v = {
    	"Alchemist",
        "BananaFarm",
        "BombShooter",
        "BoomerangMonkey",
        "DartMonkey",
        "Druid",
        "GlueGunner",
        "HeliPilot",
        "IceMonkey",
        "MonkeyAce",
        "MonkeyBuccaneer",
        "MonkeySub",
        "MonkeyVillage",
        "NinjaMonkey",
        "SniperMonkey",
        "SpikeFactory",
        "SuperMonkey",
        "TackShooter",
        "WizardMonkey",
        "MortarMonkey",
        "EngineerMonkey",
        "DartlingGunner",
        "BeastHandler"
    };

    const char** insta_monkeys = instaMonkeys_v.data();
    
    constexpr long long currentSeed = 557706693;

    SeededRandom* seeded_random = new SeededRandom();
    seeded_random->ctor(currentSeed);

    const char** result = shuffle_seeded(seeded_random, insta_monkeys, instaMonkeys_v.size(), currentSeed);

    for (int i = 0; i < instaMonkeys_v.size(); i++) {
        printf("%d: %s\n", i + 1, result[i]);
    }

    return 0;
}