#pragma once

//#include <iostream>

#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>

namespace StoSampling {

typedef size_t index_t;
typedef std::vector<double> weight_type;
typedef std::vector<index_t> trace_type;

#if 0
// commented out since we use std::discrete_distribution now to do the sampling
// prefix-sum tree data structure used to sample a given (scaled) pmf
class PrefixSumTree {
public:
    PrefixSumTree(size_t num_intervals) {
        size_t np2 = 1;
        while (np2 < num_intervals) np2 <<= 1;
        leaves_idx = np2 - 1;
        size = np2 * 2;
        array = new size_t[size];
        bzero(array, size*sizeof(size_t));
    }

    ~PrefixSumTree() {
        delete[] array;
    }

    // populate the content of the tree given a pmf
    void load(const pmf_type& pmf) {
        for (size_t i = 0; i < pmf.size(); ++i)
            increment_interval((index_t)i, pmf[i]);
    }

    // this is the "sample" method
    index_t find_interval(size_t prefix_sum) const {
        assert(prefix_sum <= array[0]);
        index_t p = 0;
        while (p < leaves_idx) {
            index_t left = p*2+1;
            index_t right = p*2+2;
            size_t al = array[left];
            if (al >= prefix_sum) {
                p = left;
            } else {
                prefix_sum -= al;
                p = right;
                assert(prefix_sum <= array[right]);
            }
        }
        return p - leaves_idx; 
    }

    size_t adjusted_resolution() const {
        return array[0];
    }

private:
    // helper function which incrementally updates the content of the tree
    // while maintaining data structure invariants
    void increment_interval(index_t index, size_t amount) {
        index += leaves_idx;
        while (true) {
            array[index] += amount;
            if (index == 0)
                break;
            index = (index - 1)/2;
        } 
    }

    size_t *array;
    size_t size;
    size_t leaves_idx;
};
#endif

template <typename IntType>
class StoUniformIntSampler {
public:
    StoUniformIntSampler() : rd(), gen(rd()), dis() {}
    StoUniformIntSampler(IntType range)
        : rd(), gen(rd()), dis(0, range-1) {}

    IntType sample() {
        return dis(gen);
    }

    void set_params(typename std::uniform_int_distribution<IntType>::param_type p) {
        dis.param(p);
    }

    std::mt19937& generator() {
        return gen;
    }

private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<IntType> dis;
};

// Parameters
// n: size of the universe
// shuffle: generate a random mapping from sampled indices to actual indices used in experiments
// index_table: set a custom index translation table
class StoRandomDistribution {
public:
    StoRandomDistribution(size_t n, bool shuffle = false)
        : n_(n), index_transform(false), uis(), dist() {
        if (shuffle) {
            std::random_device rd;
            std::mt19937 gen(rd());
            index_transform = true;

            for (size_t i = 0; i < n_; ++i)
                index_translation_table.push_back(i);
            std::shuffle(index_translation_table.begin(), index_translation_table.end(), gen);
        }
    }
    StoRandomDistribution(size_t n, std::vector<index_t> index_table)
        : n_(n), index_transform(true), index_translation_table(index_table),
        uis(), dist() {}

    virtual ~StoRandomDistribution() {}

    virtual index_t sample() const {
        auto s_index = dist(uis.generator());
        if (index_transform) {
            return index_translation_table[s_index];
        } else {
            return s_index;
        }
    }

    trace_type sample_trace(size_t num_samples) const {
        trace_type trace;
        for (size_t i = 0; i < num_samples; ++i)
            trace.push_back(sample());
        return trace;
    }

protected:
    void generate() {
        weight_type pmf = generate_weights();
        std::discrete_distribution<index_t> d_(pmf.begin(), pmf.end());
        dist.param(d_.param());
    }

    // this is the method specific to each prob. distribution
    virtual weight_type generate_weights() = 0;

    size_t n_;
    bool index_transform;
    std::vector<index_t> index_translation_table;

    mutable StoUniformIntSampler<index_t> uis;
    // the core distribution
    mutable std::discrete_distribution<index_t> dist;
};

// specialization 1: uniform random distribution
class StoUniformDistribution : public StoRandomDistribution {
public:
    StoUniformDistribution(size_t n, bool shuffle = false) :
        StoRandomDistribution(n, shuffle) {generate();}
    StoUniformDistribution(size_t n, std::vector<index_t> index_table) :
        StoRandomDistribution(n, index_table) {generate();}

    index_t sample() const override {
        auto s_index = uis.sample();
        if (index_transform)
            return index_translation_table[s_index];
        else
            return s_index;
    }

protected:
    weight_type generate_weights() override {
        std::uniform_int_distribution<index_t> d(0, n_-1);
        uis.set_params(d.param());
        return weight_type();
    }
};

// specialization 2: zipf distribution
class StoZipfDistribution : public StoRandomDistribution {
public:
    static constexpr double default_skew = 1.0;

    StoZipfDistribution(size_t n, double skew = default_skew, bool shuffle = false) :
        StoRandomDistribution(n, shuffle), skewness(skew) {
        calculate_sum();
        generate();
    }
    StoZipfDistribution(size_t n, double skew, std::vector<index_t> index_table) :
        StoRandomDistribution(n, index_table), skewness(skew) {
        calculate_sum();
        generate();
    }

protected:
    weight_type generate_weights() override {
        weight_type pmf;
        for (size_t i = 0; i < n_; ++i) {
            double p = 1.0/(std::pow((double)(i+1), skewness)*sum_);
            //std::cout << p << std::endl;
            pmf.push_back(p);
        }
        return pmf;
    }

private:
    void calculate_sum() {
        double s = 0.0;
        for (size_t i = 1; i <= n_; ++i)
            s += std::pow(1.0/(double)i, skewness);
        sum_ = s;
    }

    double skewness;
    double sum_;
};

}; // namespace StoSampling
