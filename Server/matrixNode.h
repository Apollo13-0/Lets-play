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

private:
    int _position = 0;

    bool _obstacule = false;
};


#endif //SERVER_MATRIXNODE_H


