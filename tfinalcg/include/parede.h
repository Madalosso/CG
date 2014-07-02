#ifndef PAREDE_H
#define PAREDE_H


class parede
{
    public:
        float pos_x;
        float largura;
        float gap_up,gap_down;

        parede(float tam, float largura_in);
        virtual ~parede();
        void draw();
    protected:
    private:
};

#endif // PAREDE_H
