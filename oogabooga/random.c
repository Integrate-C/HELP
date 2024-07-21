// LCG
// Meh distribution, but good enough for general purposes

#define RAND_MAX_64 0xFFFFFFFFFFFFFFFFull
#define MULTIPLIER 6364136223846793005ull
#define INCREMENT 1442695040888963407ull

// set this to something like os_get_current_cycle_count() for very randomized seed
u64 seed_for_random = 2;

u64 get_random() {
    seed_for_random = seed_for_random * MULTIPLIER + INCREMENT;
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
    // Supporting larger values for n would requires an even more
    // elaborate implementation that combines multiple calls to rand()
    assert (n <= RAND_MAX)

    // Chop off all of the values that would cause skew...
    int end = RAND_MAX / n; // truncate skew
    assert (end > 0);
    end *= n;

    // ... and ignore results from rand() that fall above that limit.
    // (Worst case the loop condition should succeed 50% of the time,
    // so we can expect to bail out of this loop pretty quickly.)
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

s64 get_random_int_in_range(s64 min, s64 max) {
    return min + (s64)(get_random() % (max - min + 1));
}