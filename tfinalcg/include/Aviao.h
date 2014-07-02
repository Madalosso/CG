#ifndef AVIAO_H
#define AVIAO_H


class Aviao
{
    public:
        float pos_x,pos_y;
        float tam,ang;
        bool subindo;

        Aviao();
        virtual ~Aviao();
        void draw();
    protected:
    private:
};

#endif // AVIAO_H
