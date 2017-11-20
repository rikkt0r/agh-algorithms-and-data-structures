#ifndef PI_H
#define PI_H


class Pi {
public:
    Pi();
    ~Pi();
    void integralSingleThread(int parts);
    void integralMultiThreadedReduction(int parts);
    void integralMultiThreadedSequential(int parts);
    void integralMultiThreadedNonSequential(int parts);
    void moneteCarloSingleThread(int seeds);
    void moneteCarloMultiThreadReduction(int seeds);
    void moneteCarloMultiThread(int seeds);
};

#endif // PI_H
