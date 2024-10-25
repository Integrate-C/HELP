// LCG
// Meh distribution, but good enough for general purposes

#define RAND_MAX_64 0xFFFFFFFFFFFFFFFFull
#define MULTIPLIER 6364136223846793005ull
#define INCREMENT 1442695040888963407ull

// #Global
// set this to something like rtdsc() for very randomized seed
ogb_instance thread_local u64 seed_for_random;

#if !OOGABOOGA_LINK_EXTERNAL_INSTANCE
thread_local u64 seed_for_random = 1;
#endif

// Like get_random but it doesn't advance the seed
u64 peek_random() {
    return seed_for_random * MULTIPLIER + INCREMENT;
}

u64 get_random() {
    seed_for_random = peek_random();
    return seed_for_random;
}

u64 get_random_from_seed(u64 seed) {
	seed = seed * MULTIPLIER + INCREMENT;
    return seed;
}

int uniform_distribution(int rangeLow, int rangeHigh) {
    double myRand = rand()/(1.0 + RAND_MAX); 
    int range = rangeHigh - rangeLow + 1;
    int myRand_scaled = (myRand * range) + rangeLow;
    return myRand_scaled;
}

int randint(int n) {
  if ((n - 1) == RAND_MAX) {
    return rand();
  } else {
    assert (n <= RAND_MAX)

    int end = RAND_MAX / n;
    assert (end > 0);
    end *= n;

    int r;
    while ((r = rand()) >= end);

    return r % n;
  }
}

f32 get_random_float32() {
	return (float32)get_random()/(float32)UINT64_MAX;
}

f64 get_random_float64() {
	return (float64)get_random()/(float64)UINT64_MAX;
}


f32 get_random_float32_in_range(f32 min, f32 max) {
	return (max-min)*get_random_float32()+min;
}
f64 get_random_float64_in_range(f64 min, f64 max) {
	return (max-min)*get_random_float64()+min;
}

// in_range max is --->INCLUSIVE<---
s64 get_random_int_in_range(s64 min, s64 max) {
    if (min == max) return 0;
    if (min > max) swap(min, max, s64);

    return min + (s64)(get_random() % (max - min + 1));
}