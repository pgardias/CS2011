// pmgardias - Przemek Gardias

#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <strings.h>
#include <math.h>

typedef unsigned long long int memHold;

typedef struct addr {
    int v;
    memHold t;
    char *address;
    int counter;
} addr;

typedef struct addrs {
    addr *addresses;
} addrs;

typedef struct cache {
    addrs *cache;
} cache;

typedef struct params {
    int s, b, E, S, B;
    int hits, misses, evictions;
} params;

int v;

// Find power by shifting bits
long long powBit(int pow) {
    long long ans = 1;
    ans = ans << pow;
    return ans;
}

// Create cache
cache makeCache (long long s, int l, long long bs) {
    cache newCache;
    addrs myAddresses;
    addr myAddress;

    newCache.cache = (addrs *) malloc(sizeof(addrs) * s);
    for (int i = 0; i < s; i++) {
    	myAddresses.addresses = (addr *) malloc(sizeof(addr) * l);
        newCache.cache[i] = myAddresses;
        for (int j = 0; j < l; j ++) {
        	myAddress.counter = 0;
        	myAddress.v = 0;
        	myAddress.t = 0;
            myAddresses.addresses[j] = myAddress;
        }
    }
    return newCache;
}

// Empty cahche
void emptyCache(cache myCache, long long s, int l, long long bs) {
    for (int i = 0; i < s; i++) {
        addrs set = myCache.cache[i];
        if (set.addresses != NULL) {
            free(set.addresses);
        }
    }
    if (myCache.cache != NULL) {
        free(myCache.cache);
    }
}

// Find empty address
int emptyAddr(addrs s, params param) {
    addr myAddress;
    int i;

    for (i = 0; i < param.E; i++) {
    	myAddress=s.addresses[i];
        if(myAddress.v == 0) {
            return i;
        }
    }
    return 0;
}

// Find least recently used
int leastRecentlyUsed (addrs s, params param, int *used_lines) {
    int max = s.addresses[0].counter;
    int min = s.addresses[0].counter;
    int minIndex = 0;

    for (int i = 1; i < param.E; i++) {
    	addr myAddress=s.addresses[i];
        if (min > myAddress.counter) {
            minIndex = i ;
            min = myAddress.counter;
        }
        if (max < myAddress.counter) {
            max = myAddress.counter;
        }
    }
    
    // Reset cache array position
    used_lines[0] = min;
    used_lines[1] = max;
    return minIndex;

}

// Cache simulation
params sim(cache myCache, params param, memHold address) {
        int sizeTag = 64 - (param.s + param.b);
        unsigned long long tempTag = address << sizeTag;
        unsigned long long newIndex = tempTag >> (sizeTag + param.b);
        memHold newTag = address >> (param.s+param.b);
        addrs cacheQuery = myCache.cache[newIndex];
        int origHit = param.hits;
        int flag = 1;
        int *checked =(int*) malloc(sizeof(int) * 2);
        int min_used_index = leastRecentlyUsed(cacheQuery, param, checked);

        for (int i = 0; i < param.E; i++) {
            addr myAddress = cacheQuery.addresses[i];
            if (myAddress.v) {
                if (myAddress.t == newTag) {
                	myAddress.counter++;
                    param.hits++;
                    cacheQuery.addresses[i] = myAddress;
                }
            } else if (!(myAddress.v) && flag) {
            	flag = 0;
            }
        }
        if (origHit == param.hits) {
            param.misses++;
        } else {
            return param;
        }
        if (flag) {
            param.evictions++;
            cacheQuery.addresses[min_used_index].t = newTag;
            cacheQuery.addresses[min_used_index].counter = checked[1] + 1;
        } else {
            int emptyLine = emptyAddr(cacheQuery,param);
            cacheQuery.addresses[emptyLine].t = newTag;
            cacheQuery.addresses[emptyLine].v = 1;
            cacheQuery.addresses[emptyLine].counter = checked[1] + 1;
        }
        free(checked);
        return param;
}

int main(int argc, char **argv) {
    cache myCache;
    params param;
    bzero(&param,sizeof(param));
    long long s, bs;
    FILE *f;
    memHold bits;
    int size;
    char *readF, c, input;

    while ((c = getopt(argc, argv, "s:E:b:t:vh")) != -1) {
        switch(c) {
        case 's':
        	param.s = atoi(optarg);
            break;
        case 'E':
        	param.E = atoi(optarg);
            break;
        case 'b':
        	param.b = atoi(optarg);
            break;
        case 't':
            readF = optarg;
            break;
        case 'v':
            v = 1;
            break;
        case 'h':
            exit(0);
        default:
            exit(1);
        }
    }

    s = pow(2.0,param.s);
    bs = powBit(param.b);
    param.hits = param.misses = param.evictions = 0;
    myCache = makeCache(s, param.E, bs);
    f = fopen(readF, "r");

    // Scan file
   	if (f != NULL) {
        while (fscanf(f, " %c %llx,%d", &input, &bits, &size) == 3) {
            switch(input) {
                case 'I':
                	break;
                case 'L':
                    param = sim(myCache, param, bits);
                    break;
                case 'S':
                	param = sim(myCache, param, bits);
                	break;
                case 'M':
                	param = sim(myCache, param, bits);
                	param = sim(myCache, param, bits);
                	break;
                default:
                break;
            }
        }
    }
    printSummary(param.hits, param.misses, param.evictions);
    emptyCache(myCache, s, param.E, bs);
    fclose(f);
    return 0;
}
