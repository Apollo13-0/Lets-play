//
// Created by usuario on 5/18/21.
//

#include "matrixNode.h"

int matrixNode::getPosition() const {
    return _position;
}

void matrixNode::setPosition(int position) {
    _position = position;
}

bool matrixNode::isObstacule() const {
    return _obstacule;
}

void matrixNode::setObstacule(bool obstacule) {
    _obstacule = obstacule;
}
