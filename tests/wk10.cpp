bool LinkedList::contains(int value, Node* node) {
        bool retVal = false;
        if (node == nullptr) {
                retVal = false;
        } 
        else if (node->data == value) {
                retVal = true;
        } 
        else {
                retVal = contains(value, node->next);
        }
        
        return retVal;
}