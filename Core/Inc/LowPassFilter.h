#ifndef UNSPRUNG_FIRMWARE_LOWPASSFILTER_H
#define UNSPRUNG_FIRMWARE_LOWPASSFILTER_H

/**
 * Just copied from VCU CORE
 */

/**
 * Digital Low Pass Filter: http://techteach.no/simview/lowpass_filter/doc/filter_algorithm.pdf
 */
class LowPassFilter {
private:
    float timeConstant;
    float accumulator;
public:
    explicit LowPassFilter(float timeConstant);
    void add(float value, float deltaTime);
    float get();
    void reset();
};


#endif //UNSPRUNG_FIRMWARE_LOWPASSFILTER_H
