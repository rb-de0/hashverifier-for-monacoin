CC := gcc

release: main.c
	gcc main.c Lyra2RE/Lyra2RE.c Lyra2RE/Lyra2.c Lyra2RE/Sponge.c Lyra2RE/groestl.c Lyra2RE/blake.c Lyra2RE/bmw.c Lyra2RE/cubehash.c Lyra2RE/keccak.c Lyra2RE/skein.c -o hashverifier-for-monacoin

