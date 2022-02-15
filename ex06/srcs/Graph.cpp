#include "Graph.hpp"

Graph::Graph(char value, int mode)
    : _left(nullptr), _right(nullptr), _value(value), _mode(mode) {}

Graph::Graph(Graph &copy) 
    : _left(nullptr), _right(nullptr), _value(copy._value), _mode(copy._mode) {
    if (copy._left)
        _left = new Graph(*copy._left);
    if (copy._right)
        _right = new Graph(*copy._right);
}


int Graph::is_leaf()
{
    if (!_mode && (_value == '0' || _value == '1'))
        return (1);
    else if (_mode && (_value >= 'A' && _value <= 'Z'))
        return (1);
    return (0);
}

int Graph::insert(Graph *child)
{
    if (_right == nullptr)
    {
        _right = child;
        return (1);
    }
    else if (_right != nullptr && !_right->is_leaf() && _right->insert(child))
        return (1);
    else if (_left != nullptr && !_left->is_leaf() && _left->insert(child))
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
    else if (!is_leaf())
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
    if (!_mode) {
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
    } else
        return (0);
}

std::string Graph::to_cnf_string() {
    std::string res = "";
    if (_right)
        res += _right->to_cnf_string();
    res += _value;
    if (_left)
        res += _left->to_cnf_string();
    return (res);
}

void Graph::convert_to_cnf() {
    if (_value == '!' && _right && _right->_value == '&')
    {
        _value = '|';
        Graph *backup_left = new Graph(*_right->_left);
        Graph *backup_right = new Graph(*_right->_right);

        delete _right;

        _left = new Graph('!', _mode);
        _right = new Graph('!', _mode);

        _left->_right = backup_left;
        _right->_right = backup_right;

        convert_to_cnf();
        return ;
    }
    else if (_value == '!' && _right && _right->_value == '|')
    {
        _value = '&';
        Graph *backup_left = new Graph(*_right->_left);
        Graph *backup_right = new Graph(*_right->_right);

        delete _right;

        _left = new Graph('!', _mode);
        _right = new Graph('!', _mode);

        _left->_right = backup_left;
        _right->_right = backup_right;
    }
    else if (_value == '>')
    {
        _value = '|';
        Graph *backup_left = _left;

        _left = new Graph('!', _mode);

        _left->_right = backup_left;
    }
    else if (_value == '^')
    {
        _value = '&';
        Graph *backup_left = _left;
        Graph *backup_right = _right;

        _left = new Graph('!', _mode);
        _right = new Graph('|', _mode);

        _right->_left = new Graph(*backup_left);
        _right->_right = new Graph(*backup_right);

        _left->_right = new Graph('&', _mode);

        _left->_right->_left = backup_left;
        _left->_right->_right = backup_right;
    }
    else if (_value == '=')
    {
        _value = '|';
        Graph *backup_left = _left;
        Graph *backup_right = _right;

        _left = new Graph('&', _mode);
        _right = new Graph('&', _mode);

        _left->_left = backup_left;
        _left->_right = backup_right;

        _right->_left = new Graph('!', _mode);
        _right->_left->_right = new Graph(*backup_left);

        _right->_right = new Graph('!', _mode);
        _right->_right->_right = new Graph(*backup_right);
        convert_to_cnf();
        return;
    }
    else if (_value == '|' && _right->_value == '&')
    {
        _value = '&';
        Graph *backup_left = _left;
        Graph *backup_right_left = new Graph(*_right->_left);
        Graph *backup_right_right = new Graph(*_right->_right);

        delete _right;

        _left = new Graph('|', _mode);
        _right = new Graph('|', _mode);

        _left->_left = backup_left;
        _left->_right = backup_right_left;

        _right->_left = new Graph(*backup_left);
        _right->_right = backup_right_right;
    }
    else if (_value == '|' && _left->_value == '&')
    {
        _value = '&';
        Graph *backup_left = _right;
        Graph *backup_right_left = new Graph(*_left->_left);
        Graph *backup_right_right = new Graph(*_left->_right);

        delete _left;

        _left = new Graph('|', _mode);
        _right = new Graph('|', _mode);

        _left->_left = backup_left;
        _left->_right = backup_right_left;

        _right->_left = new Graph(*backup_left);
        _right->_right = backup_right_right;
    }
    if (_left)
        _left->convert_to_cnf();
    if (_right)
        _right->convert_to_cnf();
}

std::string Graph::to_nnf_string() {
    std::string res = "";
    if (_left)
        res += _left->to_nnf_string();
    if (_right)
        res += _right->to_nnf_string();
    return (res + _value);
}

void Graph::convert_to_nnf() {
    if (_value == '!' && _right && _right->_value == '&')
    {
        _value = '|';
        Graph *backup_left = new Graph(*_right->_left);
        Graph *backup_right = new Graph(*_right->_right);

        delete _right;

        _left = new Graph('!', _mode);
        _right = new Graph('!', _mode);

        _left->_right = backup_left;
        _right->_right = backup_right;
    }
    else if (_value == '!' && _right && _right->_value == '|')
    {
        _value = '&';
        Graph *backup_left = new Graph(*_right->_left);
        Graph *backup_right = new Graph(*_right->_right);

        delete _right;

        _left = new Graph('!', _mode);
        _right = new Graph('!', _mode);

        _left->_right = backup_left;
        _right->_right = backup_right;
    }
    else if (_value == '>')
    {
        _value = '|';
        Graph *backup_left = _left;

        _left = new Graph('!', _mode);

        _left->_right = backup_left;
    }
    else if (_value == '^')
    {
        _value = '&';
        Graph *backup_left = _left;
        Graph *backup_right = _right;

        _left = new Graph('!', _mode);
        _right = new Graph('|', _mode);

        _right->_left = new Graph(*backup_left);
        _right->_right = new Graph(*backup_right);

        _left->_right = new Graph('&', _mode);

        _left->_right->_left = backup_left;
        _left->_right->_right = backup_right;
    }
    else if (_value == '=')
    {
        _value = '|';
        Graph *backup_left = _left;
        Graph *backup_right = _right;

        _left = new Graph('&', _mode);
        _right = new Graph('&', _mode);

        _left->_left = backup_left;
        _left->_right = backup_right;

        _right->_left = new Graph('!', _mode);
        _right->_left->_right = new Graph(*backup_left);

        _right->_right = new Graph('!', _mode);
        _right->_right->_right = new Graph(*backup_right);
    }
    if (_left)
        _left->convert_to_nnf();
    if (_right)
        _right->convert_to_nnf();
}

int Graph::max_depth() {
    int left_depth = 0, right_depth = 0;

    if (_left)
        left_depth = _left->max_depth();
    if (_right)
        right_depth = _right->max_depth();
    return((left_depth > right_depth ? left_depth : right_depth) + 1);
}

void Graph::free_childs() {
    if (_left)
        _left->free_childs();
    if (_right)
        _right->free_childs();
    delete this;
}

void Graph::_print_graph_utils(int current_level, bool side, int *dirswap) {
		std::string color = "\033[1;44m";
		std::string pipe = "\033[1;34m";
		std::string reset = "\033[0m";
		std::stringstream ss;

		for (int i = 0; i < current_level - 1; i++)
			if (dirswap[i])
				ss << "  " << pipe << "│" << reset << "  ";
			else
				ss << "     ";
		
		if (!current_level)
			ss << " " << color << " ";
		else if (!side)
			ss << "  " << pipe << "╰───" << reset << color << " ";
		else
			ss << "  " << pipe << "╭───" << reset << color << " ";

		ss << _value << " ";
		ss << reset << std::endl;
		std::cout << ss.str();
}

void Graph::_print_graph(int current_level, bool side, int *dirswap) {
    if (_right)
    {
        if (side != 1 && current_level != 0)
            dirswap[current_level - 1] = 1;
        else if (current_level != 0)
            dirswap[current_level - 1] = 0;
        _right->_print_graph(current_level + 1, 1, dirswap);
    }
    _print_graph_utils(current_level, side, dirswap);
    if (_left)
    {
        if (side != 0 && current_level != 0)
            dirswap[current_level - 1] = 1;
        else if (current_level != 0)
            dirswap[current_level - 1] = 0;
        _left->_print_graph(current_level + 1, 0, dirswap);
    }
}

void Graph::print() {
    int max_depth = this->max_depth();
    int i[max_depth];
		for (int j = 0; j < max_depth - 1; j++)
			i[j] = 0;
    _print_graph(0, 0, i);
    std::cout << std::endl << std::endl;
}

Graph::~Graph() {
    delete _left;
    delete _right;
}