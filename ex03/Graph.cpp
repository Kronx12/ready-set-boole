#include "Graph.hpp"

Graph::Graph(char value)
    : _left(nullptr), _right(nullptr), _value(value) {}

int Graph::insert(Graph *child)
{
    if (_right == nullptr)
    {
        _right = child;
        return (1);
    }
    else if (_right != nullptr && _right->_value != '0' && _right->_value != '1' && _right->insert(child))
        return (1);
    else if (_left != nullptr && _left->_value != '0' && _left->_value != '1' && _left->insert(child))
        return (1);
    else if (_left == nullptr && _value != '!')
    {
        _left = child;
        return (1);
    }
    return (0);
}

int Graph::check_graph()
{
    if (_left)
        return (_left->check_graph());
    else if (_value != '0' && _value != '1')
    {
        if (_value != '!' || (_value == '!' && _right == nullptr))
            return (1);
        else
            return (0);
    }
    else
        return (0);
}

int Graph::compute()
{
    int left = -2;
    int right = -2;

    if (_left)
        left = _left->compute();
    if (_right)
        right = _right->compute();
    if (left == -1 || right == -1)
        return (-1);
    switch (_value)
    {
    case '0':
        return (0);
    case '1':
        return (1);
    case '!':
        return (!right);
    case '&':
        return (left & right);
    case '|':
        return (left || right);
    case '^':
        return (left ^ right);
    case '>':
        return (right >= left);
    case '=':
        return (left == right);
    default:
        return -1;
    }
}

Graph::~Graph() {}