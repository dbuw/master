#ifndef RANDOM_H
#define RANDOM_H


class Random
{
    public:
        Random();
        int uniformRandomInt();
        int randomInt(int min, int max){
            return 4;
        }
        int randomize(){
            //random number between [0,1]*precision
            return 5;
        }
    private:
        Parameters* param;

};

#endif // RANDOM_H
