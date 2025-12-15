#include "../struct/enemy.h"

class SpringTime : public Enemy
{
private:
    void getMovePosition() override;

public:
    SpringTime(std::shared_ptr<nightDB> data, size_t ID);

    bool move(bool doorStatus) override;
};