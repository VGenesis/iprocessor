#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

template <typename T>
class List{
    private:
        struct ListNode{
            T* data;
            ListNode* next;
        };

        ListNode* head;

    public:
        List(){
            head = (ListNode*) malloc(sizeof(ListNode));
            head->data = NULL;
            head->next = nullptr;
        }

        void add(T* node){
            ListNode newNode = {node, NULL};
            if(head->data == NULL){
                head = &newNode;
            } else {
                head->next = &newNode; 
            }
        }

        T* get(int index){
            ListNode* iter = head;
            while(iter){
                if(index == 0) 
                    return (iter)? iter->data : nullptr;
                iter = iter->next;
            }
            return nullptr;
        }

        void remove(int index){
            ListNode* iter = head;
            while(iter){
                if(index == 1){
                    ListNode* removed = iter->next;
                    if(removed){
                        iter->next = removed->next;
                        removed->next = nullptr;
                        free(removed);
                        return;
                    }
                }
                iter = iter->next;
            }
        }

        int size(){
            ListNode* iter = head;
            int size = 0;
            while(iter != nullptr){
                if(iter->data != NULL) size++;
                iter = iter->next;
            }
            return size;
        }
};
