//
// Created by usuario on 5/18/21.
//

#ifndef SERVER_MATRIXNODE_H
#define SERVER_MATRIXNODE_H


class matrixNode {
public:
    int getPosition() const;

    void setPosition(int position);

    bool isObstacule() const;

    void setObstacule(bool obstacule);

    int getY() const;

    void setY(int y);

    int getX() const;

    void setX(int x);

    int getParentX() const;

    void setParentX(int parentX);

    int getParentY() const;

    void setParentY(int parentY);

    float getGCost() const;

    void setGCost(float gCost);

    float getHCost() const;

    void setHCost(float hCost);

    float getFCost() const;

    void setFCost(float fCost);

private:private:
    int _position = 0;
    int y;
    int x;
    int parentX;
    int parentY;
    float gCost;
    float hCost;
    float fCost;
    bool _obstacule = false;
};


#endif //SERVER_MATRIXNODE_H


