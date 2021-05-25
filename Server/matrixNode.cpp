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

int matrixNode::getY() const {
    return y;
}

void matrixNode::setY(int y) {
    matrixNode::y = y;
}

int matrixNode::getX() const {
    return x;
}

void matrixNode::setX(int x) {
    matrixNode::x = x;
}

int matrixNode::getParentX() const {
    return parentX;
}

void matrixNode::setParentX(int parentX) {
    matrixNode::parentX = parentX;
}

int matrixNode::getParentY() const {
    return parentY;
}

void matrixNode::setParentY(int parentY) {
    matrixNode::parentY = parentY;
}

float matrixNode::getGCost() const {
    return gCost;
}

void matrixNode::setGCost(float gCost) {
    matrixNode::gCost = gCost;
}

float matrixNode::getHCost() const {
    return hCost;
}

void matrixNode::setHCost(float hCost) {
    matrixNode::hCost = hCost;
}

float matrixNode::getFCost() const {
    return fCost;
}

void matrixNode::setFCost(float fCost) {
    matrixNode::fCost = fCost;
}
