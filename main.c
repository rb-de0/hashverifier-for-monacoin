#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "Lyra2RE/Lyra2.h"
#include "Lyra2RE/Lyra2RE.h"
#include "Lyra2RE/sph_blake.h"
#include "Lyra2RE/sph_groestl.h"
#include "Lyra2RE/sph_cubehash.h"
#include "Lyra2RE/sph_bmw.h"
#include "Lyra2RE/sph_keccak.h"
#include "Lyra2RE/sph_skein.h"

void cubehash256(char* input, char* output) {
    
    uint32_t result[8];
    sph_cubehash256_context ctx_cubehash;
    
    sph_cubehash256_init(&ctx_cubehash);
    sph_cubehash256(&ctx_cubehash, input, 32);
    sph_cubehash256_close(&ctx_cubehash, result);
    
    memcpy(output, result, 32);
}

void blake256(char* input, char* output) {
    
    uint32_t result[8];
    sph_blake256_context ctx_blake;
    
    sph_blake256_init(&ctx_blake);
    sph_blake256(&ctx_blake, input, 32);
    sph_blake256_close(&ctx_blake, result);	
    
    memcpy(output, result, 32);
}

void keccak256(char* input, char* output) {
    
    uint32_t result[8];
    sph_keccak256_context ctx_keccak;
    
    sph_keccak256_init(&ctx_keccak);
    sph_keccak256(&ctx_keccak, input, 32); 
    sph_keccak256_close(&ctx_keccak, result);
    
    memcpy(output, result, 32);
}

void skein256(char* input, char* output) {
    
    uint32_t result[8];
    sph_skein256_context ctx_skein;
    
    sph_skein256_init(&ctx_skein);
    sph_skein256(&ctx_skein, input, 32); 
    sph_skein256_close(&ctx_skein, result);
    
    memcpy(output, result, 32);
}

void bmw256(char* input, char* output) {
    
    uint32_t result[8];
    sph_bmw256_context ctx_bmw;
    
    sph_bmw256_init(&ctx_bmw);
    sph_bmw256(&ctx_bmw, input, 32);
    sph_bmw256_close(&ctx_bmw, result);
    
    memcpy(output, result, 32);
}

char *algorithms[6] = {
    "lyra2rev2", 
    "lyra2",
    "blake",
    "cubehash",
    "skein",
    "bmw"
};

void print_hash(char* algorithm, char* input, char* output) {

    char input_lyra2re2[80];
    size_t input_length = strlen(input);

    if (strcmp(algorithm, "lyra2rev2") == 0) {

         for (size_t count = 0; count < sizeof(input_lyra2re2) / sizeof(*input_lyra2re2); count++) {
            if (count * 2 >= input_length) {
                input_lyra2re2[count] = 0x00;
            } 
        }

        lyra2re2_hash(input_lyra2re2, output);

    } else if (strcmp(algorithm, "blake") == 0) {
        blake256(input, output);
    } else if (strcmp(algorithm, "cubehash") == 0) {
        cubehash256(input, output);
    } else if (strcmp(algorithm, "keccak") == 0) {
        keccak256(input, output);
    } else if (strcmp(algorithm, "skein") == 0) {
        skein256(input, output);
    } else if (strcmp(algorithm, "bmw") == 0) {
        bmw256(input, output);
    } else if (strcmp(algorithm, "lyra2") == 0) {
        LYRA2(output, 32, input, 32, input, 32, 1, 4, 4);
    } else {
        printf("Algorithum not found\n");
        exit(1);
    }

    printf("%s result : ", algorithm);

    for(int i = 0; i < 32; i++) {
        printf("%02x", (unsigned char)output[i]);
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    
    char* algorithm;
    char* input;
    char input_hex[32];
    char output[32];
    bool all = false;
    
    if (argc <= 1) {
        printf("Arguments is missing\n");
        exit(1);
    }

    all = argc == 2;

    if (all) {

        input = argv[1];

        for (size_t count = 0; count < sizeof input_hex/sizeof *input_hex; count++) {
            sscanf(input, "%2hhx", &input_hex[count]);
            input += 2;
        }

        for(int i = 0; i < sizeof(algorithms) / sizeof(*algorithms); i++) {
            print_hash(algorithms[i], input_hex, output);
        }

    } else {

        algorithm = argv[1];
        input = argv[2];

        for (size_t count = 0; count < sizeof input_hex/sizeof *input_hex; count++) {
            sscanf(input, "%2hhx", &input_hex[count]);
            input += 2;
        }

        print_hash(algorithm, input_hex, output);
    }
    
    return 0;
}
