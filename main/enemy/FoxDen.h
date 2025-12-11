#include "../struct/enemy.h"

class FoxDen : public Enemy
{
private:
    void getMovePosition() override;

public:
    FoxDen(std::shared_ptr<nightDB> data, size_t ID);

    void doubleJump();

    bool move(bool doorStatus) override;
};