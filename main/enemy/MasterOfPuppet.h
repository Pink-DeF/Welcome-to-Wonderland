#include "../struct/enemy.h"

class MasterOfPuppet : public Enemy
{
private:
    void getMovePosition() override;

    void useFake();

public:
    MasterOfPuppet(std::shared_ptr<nightDB> data, size_t ID);

    bool move(bool doorStatus) override;
};