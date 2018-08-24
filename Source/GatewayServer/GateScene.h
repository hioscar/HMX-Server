#ifndef __GATE_SCENE_H_
#define __GATE_SCENE_H_


/*
 *	ʵ��˫������ľ�������
 */


#include <iostream>
#include <string>

using namespace std;

// ˫��������
class DoubleNode
{
public:
	DoubleNode(string key, int x, int y)
	{
		this->key = key;
		this->x = x;
		this->y = y;
		xPrev = xNext = NULL;
	};

	DoubleNode * xPrev;
	DoubleNode * xNext;

	DoubleNode * yPrev;
	DoubleNode * yNext;

	string key;
	int x; // λ�ã�x���꣩
	int y; // λ�ã�y���꣩

private:

};




// ��ͼ/����
class SceneNode
{
public:

	SceneNode()
	{
		this->_head = new DoubleNode("[head]", 0, 0); // ��ͷβ��˫����(���Ż�ȥ��ͷβ)
		this->_tail = new DoubleNode("[tail]", 0, 0);
		_head->xNext = _tail;
		_head->yNext = _tail;
		_tail->xPrev = _head;
		_tail->yPrev = _head;
	};

	// �������(����)
	DoubleNode * Add(string name, int x, int y)
	{

		DoubleNode * node = new DoubleNode(name, x, y);
		_add(node);
		return node;
	};

	// �����뿪(ɾ��)
	void Leave(DoubleNode * node)
	{
		node->xPrev->xNext = node->xNext;
		node->xNext->xPrev = node->xPrev;
		node->yPrev->yNext = node->yNext;
		node->yNext->yPrev = node->yPrev;

		node->xPrev = NULL;
		node->xNext = NULL;
		node->yPrev = NULL;
		node->yNext = NULL;
	};

	// �����ƶ�
	void Move(DoubleNode * node, int x, int y)
	{
		Leave(node);
		node->x = x;
		node->y = y;
		_add(node);
	};

	// ��ȡ��Χ�ڵ�AOI (����Ϊ���ҷ�Χ)
	void PrintAOI(DoubleNode * node, int xAreaLen, int yAreaLen)
	{
		cout << "Cur is: " << node->key << "��" << node->x << "," << node->y << ")" << endl;
		cout << "Print AOI:" << endl;

		// ������
		DoubleNode * cur = node->xNext;
		while (cur != _tail)
		{
			if ((cur->x - node->x) > xAreaLen)
			{
				break;
			}
			else
			{
				int inteval = 0;
				inteval = node->y - cur->y;
				if (inteval >= -yAreaLen && inteval <= yAreaLen)
				{
					cout << "\t" << cur->key << "(" << cur->x << "," << cur->y << ")" << endl;
				}
			}
			cur = cur->xNext;
		}

		// ��ǰ��
		cur = node->xPrev;
		while (cur != _head)
		{
			if ((node->x - cur->x) > xAreaLen)
			{
				break;
			}
			else
			{
				int inteval = 0;
				inteval = node->y - cur->y;
				if (inteval >= -yAreaLen && inteval <= yAreaLen)
				{
					cout << "\t" << cur->key << "(" << cur->x << "," << cur->y << ")" << endl;
				}
			}
			cur = cur->xPrev;
		}
	};

	// ���Դ���
	void PrintLink()  // ��ӡ����(��ͷ��ʼ)
	{
		// ��ӡx������
		DoubleNode * cur = _head->xNext;
		while (cur != _tail)
		{
			cout << (cur->key) << "(" << (cur->x) << "," << (cur->y) << ") -> ";
			cur = cur->xNext;
		}
		cout << "end" << endl;

		// ��ӡy������
		cur = _head->yNext;
		while (cur != _tail)
		{
			cout << (cur->key) << "(" << (cur->x) << "," << (cur->y) << ") -> ";
			cur = cur->yNext;
		}
		cout << "end" << endl;
	};

	// --------------------------------------------
	void test()
	{
		SceneNode scene = SceneNode();
		// ����
		scene.Add("a", 1, 5);
		scene.Add("f", 6, 6);
		scene.Add("c", 3, 1);
		scene.Add("b", 2, 2);
		scene.Add("e", 5, 3);
		DoubleNode * node = scene.Add("d", 3, 3);

		scene.PrintLink();
		scene.PrintAOI(node, 2, 2);

		// �ƶ�
		cout << endl << "[MOVE]" << endl;
		scene.Move(node, 4, 4);
		scene.PrintLink();
		scene.PrintAOI(node, 2, 2);

		// ɾ��
		cout << endl << "[LEAVE]" << endl;
		scene.Leave(node);
		scene.PrintLink();
	}

private:
	DoubleNode * _head;
	DoubleNode * _tail;

	void _add(DoubleNode * node)
	{
		// x�ᴦ��
		DoubleNode * cur = _head->xNext;
		while (cur != NULL)
		{
			if ((cur->x > node->x) || cur == _tail) // ��������
			{
				node->xNext = cur;
				node->xPrev = cur->xPrev;
				cur->xPrev->xNext = node;
				cur->xPrev = node;
				break;
			}
			cur = cur->xNext;
		}

		// y�ᴦ��
		cur = _head->yNext;
		while (cur != NULL)
		{
			if ((cur->y > node->y) || cur == _tail) // ��������
			{
				node->yNext = cur;
				node->yPrev = cur->yPrev;
				cur->yPrev->yNext = node;
				cur->yPrev = node;
				break;
			}
			cur = cur->yNext;
		}
	}
};



#endif

