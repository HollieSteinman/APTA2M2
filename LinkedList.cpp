
#include "LinkedList.h"

#include <iostream>

LinkedList::LinkedList()
{
   head = nullptr;
}

LinkedList::~LinkedList() {
}

void LinkedList::addFront(Tile* tile)
{
    if(tile!=nullptr)
    {
      Node* newNode = new Node(tile, head);
      head = newNode;
    }else
    {
      std::cout<<"Tried to addFront() failed, no tile to add"<<std::endl;
    }
}

void LinkedList::addBack(Tile* tile)
{
    Node* newNode = new Node(tile, nullptr);
    Node* tmphead = head;
    while(tmphead->next!=nullptr)
    {
      tmphead=tmphead->next;
    }
    tmphead->next = newNode;
}

void LinkedList::deleteFront()
{
  if(head!=nullptr)
  {
    Node* tmphead=head;
    head=head->next;
    delete tmphead;
  }else
  {
    std::cout<<"Tried to deleteFront() failed, front tile does not exist"<<std::endl;
  }
}

void LinkedList::deleteTile(Tile* tile)
{
    int check=0;
    Node* tmphead = head;
    while(tmphead->next!=nullptr)
    {
      if(tmphead->getTile()->getColour()==tile->getColour())
      {
        deleteFront();
        std::cout<<"Successfully deleted"<<std::endl;
        check++;
      }
      else if(tmphead->next->getTile()->getColour()==tile->getColour())
      {
        Node* tmpNode = tmphead->next;
        tmphead->next = tmpNode->next;

        delete tmpNode;
        std::cout<<"Successfully deleted"<<std::endl;
        check++;

      }

      tmphead = tmphead->next;
    }
    if(check==0)
      std::cout<<"tile not found"<<std::endl;
}

Tile* LinkedList::getFrontTile()
{
  if(head!=nullptr)
  {
    return head->getTile();
  }else
  {
    std::cout<<"Tried to getFrontTile() failed, front tile does not exist"<<std::endl;
    return nullptr;
  }
}
