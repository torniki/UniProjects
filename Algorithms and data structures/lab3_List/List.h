#pragma once


namespace Mine
{
    struct ListNode
    {
        int info;
        ListNode *next;
    };

	class List
	{
        public:
        List(); //�����������
        ~List(); //����������

        int viewFirstItem() const;          //��������� ������ ������� ������
        int removeFirstItem();             //������� ������ ������� ������
        void insertionInFront(int value);   //�������� ����� ������� � ������ ������
        void insertionInFront(ListNode* &elem);//�������� ������������ ������� � ������ ������

        int viewLastItem() const;           //��������� ��������� ������� ������
        int removeLastItem();              //������� ��������� ������� ������
        void insertionInEnd(int value);     //�������� ����� ������� � ����� ������
        void insertionInEnd(ListNode* &elem); //�������� ������������ ������� � ����� ������

        void insertionByIndex(int value, int index);   //�������� ����� ������� � ������ ����� �������� � ��������
        void insertionByIndex(ListNode* &elem, int index); //�������� ������������ ������� � ������ ����� �������� � ��������
        int viewByIndex(int index) const;   //��������� ������� ������ �� �������
        int removeByIndex(int index); //������� ������� ������ �� �������

        bool isEmpty() const;               //��������� ������ �� �������
        void PrintList() const;             //������� ���������� ������ �� �����

        ListNode* getHead() const;
        ListNode* getTail() const;

        private:
        ListNode *Head;
        ListNode *Tail;
	};
}
