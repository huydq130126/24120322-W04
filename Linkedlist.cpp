#include <iostream>
#include <cassert>
using namespace std;
struct dNODE
{
    int key;
    dNODE *pNext;
};

struct dList
{
    dNODE *pHead;
    dNODE *pTail;
    dList(dNODE *head = nullptr, dNODE *tail = nullptr) : pHead(head), pTail(tail) {}
};

// --- Define function prototypes ---
dNODE *createNode(int data);
dList *createList(dNODE *p_node);
bool addHead(dList *&L, int data);
bool addTail(dList *&L, int data);
bool removeHead(dList *&L);
void removeTail(dList *&L);
void removeAll(dList *&L);
void removeBefore(dList *&L, int val);
void removeAfter(dList *&L, int val);
bool addPos(dList *&L, int data, int pos);
void removePos(dList *&L, int data, int pos);
bool addBefore(dList *&L, int data, int val);
bool addAfter(dList *&L, int data, int val);
void printList(dList *L);
int countElements(dList *L);
dList *reverseList(dList *L);
void removeDuplicate(dList *&L);
bool removeElement(dList *&L, int key);

// function to create a list from an array
dList *createListFromArray(int arr[], int n)
{
    dList *newList = new dList();
    newList->pHead = nullptr;
    newList->pTail = nullptr;
    for (int i = 0; i < n; ++i)
    {
        addTail(newList, arr[i]);
    }
    return newList;
}

// function to compare two lists
bool areListsEqual(dList *list1, dList *list2)
{
    dNODE *current1 = list1 ? list1->pHead : nullptr;
    dNODE *current2 = list2 ? list2->pHead : nullptr;
    while (current1 && current2)
    {
        if (current1->key != current2->key)
        {
            return false;
        }
        current1 = current1->pNext;
        current2 = current2->pNext;
    }
    return (current1 == nullptr && current2 == nullptr);
}

// function to free the memory of a list
void freeList(dList *L)
{
    dNODE *current = L->pHead;
    while (current)
    {
        dNODE *next = current->pNext;
        delete current;
        current = next;
    }
    delete L;
}

dNODE *createNode(int data)
{   // Cap phat bo nho cho p
    dNODE * p = new dNODE();
    if (p == NULL){ 
        return NULL;
    }
    p->key = data; 
    p->pNext = NULL;
    
    return p; // Placeholder return statement
}

dList *createList(dNODE *p_node)
{   
    dList *l = new dList();
    if (l == NULL){
        return NULL;
    }
    l->pHead = p_node;
    l->pTail = p_node;
    return l; // Placeholder return statement
}

bool addHead(dList *&L, int data)
{   // Tao Node moi tu data
    dNODE *p = createNode(data);
    if (L->pHead ==NULL){ // Neu danh sach lien ket rong 
        L->pHead = p;  // ta add p lam phan tu dau tien va cuoi cung cua danh sach
        L->pTail = p; 
    }
    else{ // neu dslk khong rong
        p->pNext = L->pHead; // p se luu dia chi cua con tro tiep theo la dau cua dslk
        L->pHead =p; // cap nhat lai dau cua dslk
    }
    return true; // tra ve true khi da addHead thanh cong
}

bool addTail(dList *&L, int data) // this function is kept for createListfromArray function
{    // Tao Node moi tu data
    dNODE *newNode = createNode(data);
    if (L->pHead == NULL)
    {
        L->pHead = newNode;
        L->pTail = newNode;
    }
    else
    {
        L->pTail->pNext = newNode;
        L->pTail = newNode;
    }
    return true;
}

bool removeHead(dList *&L)
{   // Neu dslk rong thi tra ve false
    if (L== NULL || L->pHead ==NULL){
        return false;
    }
    // Tao NODE p luu gia tri dau cua dslk
    dNODE * p = L->pHead;
    L->pHead = L->pHead->pNext; // gan gia tri tiep theo cua gia tri dau cho gia tri dau
    p->pNext = NULL;
    if (L->pHead ==NULL){
        L->pTail = NULL; // Dslk da rong
    }
    
    delete p;
    return true;
    
}

void removeTail(dList *&L)
{   
    // Neu dslk rong thi khong lam gi, thoat khoi ham
    if (L==NULL || L->pHead ==NULL){
        return;
    }
    // 1 NODE
    if (L->pHead == L->pTail){
        delete L->pHead; // Neu dslk chi co 1 Node thi ta xoa Node
        L->pHead = NULL; // Dua hai con tro dau va cuoi ve NULL
        L->pTail = NULL;
        return;
    }  
    
    // Neu dslk co nhieu hon 1 NODE
    dNODE * p = L->pHead;

    while(p->pNext != L->pTail){ // Chay cho den khi p la nut truoc cuoi
        p = p->pNext;
    }
    delete L->pTail; // Xoa nut cuoi
    L->pTail = p; // dat lai con tro p_tail
    L->pTail->pNext =NULL;
}

void removeAll(dList *&L)
{
    dNODE *p;
    while(L->pHead !=NULL){ // Chay cho den khi DSLK rong
        p= L->pHead; // gan p la Node dau
        L->pHead = p->pNext; // Gan Node dau la node tiep theo cua p
        delete p; // xoa node p
    }
    L->pTail = NULL; // Khi dslk rong thi ta cap nhat lai con tro p_tail
}

// Remove a node before a given value in the list if it exists, otherwise do nothing
void removeBefore(dList *&L, int val)
{  // Neu dslk rong thi khong lam gi, thoat khoi ham
   if (L == NULL || L->pHead == NULL){
    return;
   }
   // Tao ba con tro theo thu tu sau
   dNODE * preq = NULL;
   dNODE * q = L->pHead;
   dNODE *p = q->pNext;
   // Khi con tro p khac NULL, tuc la trong dslk co it nhat hai NODE tro len
   while (p != NULL){
      if (p->key ==val){ // neu node co gia tri bang val
        if (preq != NULL){ // preq !=NULL, tuc la node can xoa khong phai node dau
            preq ->pNext = p; // Bo qua node q
            delete q; // Xoa node q
        } else {  // preq == NULL, tuc la node can xoa la node dau
            L->pHead = p; // cap nhat node dau la p
            delete q; // xoa node q
        }
        return; // sau khi xoa thi khong lam gi nua, thoat khoi ham
      }
      // tiep tuc di chuyen 3 con tro len 1 buoc
      preq = q;
      q = p;
      p = p ->pNext;
   }

}

void removeAfter(dList *&L, int val)
{   // Neu dslk rong thi khong lam gi, thoat khoi ham
    if (L==NULL || L->pHead == NULL){
        return;
    }
    // Tao node p nam dia chi node dau
    dNODE * p = L->pHead;
    while(p!=NULL){ // Neu p khac NULL, tuc la dslk khac rong
        if (p->key == val){ // neu node co gia tri bang val
            dNODE * q= p->pNext; // Tao node q luu dia chi node tiep theo cua node p
            if (q!=NULL){ // Neu node q khac NULL, tuc la sau sau node p van co phan tu
                p->pNext = q->pNext; // bo qua node q
                delete q; // xoa node q
            }
            return; // Neu q == NULL thi khong lam gi, thoat khoi ham
        }
        p= p->pNext; // dich p len 1 buoc tiep theo
    }


}

bool addPos(dList *&L, int data, int pos)
{   // Neu vi tri la so am thi tra ve false
    if (pos < 0){
        return false;
    }
    // Tao node p tu du lieu data
    dNODE *p = createNode(data);
    if (p == NULL){ // Neu khong du o nho hay con tro p khong duoc tao
        return false;
    }
    if (pos == 0) { // Neu vi tri can add o dau thi ta goi ham addHead
        return addHead(L, data);
    }
    dNODE *q = L->pHead;  // Tao node q chay tu dau
    int number = 0;  // Tao bien chi so tu 0 
    while (q!=NULL && number < pos -1){ // Duyet con tro q den node truoc vi tri pos (pos -1) hoac dung lai khi da den cuoi danh sach
        q= q->pNext;// Dich con tro q len 1 buoc
        number++; // Tang chi so len 1 don vi
    }
    // Neu q= NULL, tuc la chi so vuot ngoai so luong node cua danh sach, ta se xoa p de tranh loi va return fasle
    if(q==NULL){
        delete p;
        return false;
    }
    // Add con tro p vao vi tri pos, tuc la sau con tro q
    p->pNext = q->pNext;
    q->pNext = p;
    if (p->pNext == NULL){ // Neu p la node cuoi thi dat lai p_tail
        L->pTail = p;
    }
    // Tra ve true khi add thanh cong
    return true;
}

void removePos(dList *&L, int data, int pos)
{   // Neu vi tri la so am thi tra ve false
    if (pos < 0){
        return;
    }
    // Neu vi tri can xoa o dau thi ta goi ham removeHead
    if (pos == 0){
        removeHead(L);
        return;
    }

    dNODE* q = L->pHead;// Tao node q chay tu dau
    int number = 0; // Tao bien chi so tu 0 
    while (q!=NULL && number < pos -1){ // Duyet con tro q den node truoc vi tri pos (pos -1) hoac dung lai khi da den cuoi danh sach
        q= q->pNext; // Dich con tro q len 1 buoc
        number ++; // Tang chi so len 1 don vi
    }
    if (q != NULL){ // Neu q khac NULL, tuc la pos nam trong dslk
        dNODE * tmp = q->pNext; // Tao con tro tam de luu node tiep theo cua q
        q->pNext = tmp ->pNext; // bo qua con tro tmp
        if (tmp == L->pTail){ // Neu tmp la node cuoi thi ta cap nhat node cuoi
            L->pTail = q;
        }
        delete tmp; // xoa tmp
    }
   
}

// Insert an integer before a value of a given List:
bool addBefore(dList *&L, int data, int val)
{   // Tao node p tu du lieu data
    dNODE * p = createNode (data);
    // Neu dslk rong thi return fasle
    if (!p || L ==NULL || L->pHead == NULL){
        return false;
    }  
    // Neu node dau co gia tri bang val
    if (L->pHead->key == val){
        p->pNext = L->pHead; // Them node p vao dau
        L->pHead = p; // cap nhat lai p_head
        return true; // tra ve true
    }
    // Tao con tro q chay tu dau
    dNODE * q = L->pHead;
    // chay con tro q cho den khi con tro tiep theo cua q co gia tri bang val
    while (q->pNext !=NULL && q->pNext->key != val){
        q = q->pNext; // Tang q len 1 buoc
    }
    // Ta phai xet lai de kiem tra chac chan co node key = val
    if (q->pNext != NULL){
        p->pNext = q->pNext; // Them p vao sau node q, do q la node truoc node co gia tri bang val
        q->pNext = p; 
        return true; // Tra ve true
    }
    delete p; // Xoa p de khong bi loi neu khong add duoc
    return false; // Tra ve false neu khong add duoc
}

bool addAfter(dList *&L, int data, int val)
{   // Tao node p tu du lieu data
    dNODE *p = createNode(data);
    // Neu dslk rong thi tra ve false
    if (!p || L == NULL || L->pHead == NULL) {
        return false;
    }
    // Neu node dau tien cua dslk co gia tri bang val
    if(L->pHead->key == val){
        // Chen node p vao sau node dau
        p-> pNext = L->pHead->pNext;
        L->pHead->pNext = p;
        return true; // tra ve true
    }
    // Tao con tro q chay tu dau 
    dNODE *q = L->pHead;
    // Chay vong lap cho den khi q khac NULL va q co gia tri bang val
    while (q!= NULL && q->key != val){
        q=q->pNext;
    }
    //Kiem tra lai co node q->key == value khonh
    if (q!=NULL){
        // Chen p vao sau node q
        p->pNext = q->pNext;
        q->pNext =p;
        if (L->pTail == q){// Neu q la node cuoi thi cap nhat lai node cuoi la p
            L->pTail =p;
            p->pNext = NULL;
        }
        return true;
    }
    delete p;// Xoa p de tranh loi

    return false;
}
//Check
void printList(dList *L)
{
    dNODE *p = L->pHead;
    while (p != NULL)
    {
        cout << p->key << "->";
        p = p->pNext;
    }
    cout << "NULL" << endl;
}

int countElements(dList *L)
{
    dNODE * p= L->pHead;// Tao Node p tu vi tri dau
    int count = 0; // Bien dem so luong count 
    while (p!=NULL){ // Duyet tu dau den cuoi dslk
        p = p->pNext; // Chuyen qua Node tiep theo
        count++; // Tang bien dem 
    }

    return count; // Tra ve tong so node
}

dList *reverseList(dList *L)
{   // Neu dslk rong thi ta can tra ve mot dslk moi cung rong
    if (L == NULL|| L->pHead == NULL) {
    dList *p = createList(NULL);
    return p;
    }
    // Tao mot List rong de chua cac node da dao nguoc
    dList* reverseList = createList(NULL);
    // Cho con tro q chay tu dau den cuoi
    dNODE* q = L->pHead;
    while (q != NULL) {
        dNODE* newNode = new dNODE(); // Tao mot node moi luu gia tri cua node hien tai
        newNode->key = q->key;
        // Them node moi vao dau dslk moi
        newNode->pNext = reverseList->pHead;
        reverseList->pHead = newNode;// cap nhat lai p_head
        // Neu duoi cua dslk rong, cap nhat duoi cua dslk la node moi
        if (reverseList->pTail == NULL) {
            reverseList->pTail = newNode;
        }
        // dich con tro q len 1 buoc
        q = q->pNext;
    }
    // Tra ve dslk vua dao nguoc
    return reverseList;
}

void removeDuplicate(dList *&L)
{   // Neu dslk rong thi khong lam gi ca
    if (L == NULL || L->pHead == NULL) 
        return;
    // Cho node q chay tu dau den cuoi
    dNODE *q = L->pHead;
    while (q != nullptr)
    {   // Cho node p chay tu q den gan cuoi
        dNODE *p = q;
        while (p->pNext != NULL)
        {   // Neu phan tu ngay sau p co gia tri trung voi node q 
            if (p->pNext->key == q->key)
            {  // Tao mot node moi luu dia chi cua node trung
                dNODE *duplicate = p->pNext;
                // bo qua node trung
                p->pNext = p->pNext->pNext;
                // neu node trung la node cuoi thi can cap nhat lai
                if (duplicate == L->pTail) 
                    L->pTail = p;
                // Xoa node trung 
                delete duplicate;
            }
            // Neu khong trung thi ta duyet node tiep theo
            else
            {
                p = p->pNext;
            }
        }
        // Sau khi da xu ly het cac node trung cua q, ta duyet sang node tiep theo
        q = q->pNext;
    }
}

bool removeElement(dList *&L, int key)
{   // Neu ham rong thi tra ve false, khong xoa
    if (L == NULL || L->pHead == NULL) { 
        return false;
    }
    // Tao con tro p chay tu dau va con tro rong q
    dNODE *p = L->pHead;
    dNODE *q = NULL;
    // Chay con tro p tu dau den khi node co gia tri bang key
    while ((p != NULL) && (p->key != key)) {
        q = p; // Luu dia chi node truoc p 
        p = p->pNext; // Dich con tro p len
    }
    // Kiem tra chac chan ton tai node p co gia tri bang key
    if (p != NULL) {
        if (q == NULL) { // Node can xoa o dau
            L->pHead = p->pNext; // Cap nhat lai p_head
        } else {
            q->pNext = p->pNext;
        }
        // Neu node can xoa o cuoi, can cap nhat lai p_tail
        if (L->pTail == p) {
            L->pTail = q;
        }
        delete p; // xoa p
        return true;
    }
    return false;
}

// --- Function main to test the above functions ---

int main()
{
    std::cout << "--- Begin running test cases ---" << std::endl;

    // Test case 1: createNode /////////////////////////////////////////////////
    std::cout << "Test createNode: ";
    dNODE *node1 = createNode(10);
    assert(node1 != nullptr && node1->key == 10 && node1->pNext == nullptr);
    std::cout << "Passed" << std::endl;
    delete node1;

    // Test case 2: createList //////////////////////////////////////////////////
    std::cout << "Test createList: ";
    dNODE *head2 = createNode(20);
    dList *list2 = createList(head2);
    assert(list2 != nullptr && list2->pHead == head2 && list2->pTail == head2);
    std::cout << "Passed" << std::endl;
    freeList(list2);

    // Test case 3: addHead //////////////////////////////////////////////////////
    std::cout << "Test addHead: ";
    dList *list3 = new dList();
    assert(addHead(list3, 30));
    assert(list3->pHead != nullptr && list3->pHead->key == 30 && list3->pTail->key == 30);
    assert(addHead(list3, 40));
    assert(list3->pHead->key == 40 && list3->pHead->pNext->key == 30 && list3->pTail->key == 30);
    std::cout << "Passed" << std::endl;
    freeList(list3);

    // Test case 4: addTail /////////////////////////////////////////////////////////
    std::cout << "Test addTail: ";
    dList *list4 = new dList();
    assert(addTail(list4, 50));
    assert(list4->pHead != nullptr && list4->pHead->key == 50 && list4->pTail->key == 50);
    assert(addTail(list4, 60));
    assert(list4->pHead->key == 50 && list4->pTail->key == 60 && list4->pHead->pNext->key == 60);
    std::cout << "Passed" << std::endl;
    freeList(list4);

    // Test case 5: removeHead //////////////////////////////////////////////////////////////////
    std::cout << "Test removeHead: ";
    int arr1[3] = {70, 80, 90};
    dList *list5 = createListFromArray(arr1, 3);
    assert(removeHead(list5) && list5->pHead->key == 80);
    assert(removeHead(list5) && list5->pHead->key == 90);
    assert(removeHead(list5) && list5->pHead == nullptr && list5->pTail == nullptr);
    assert(!removeHead(list5)); // Remove from empty list
    std::cout << "Passed" << std::endl;
    freeList(list5);

    // Test case 6: removeTail ///////////////////////////////////////////////////////////////////
    std::cout << "Test removeTail: ";
    int arr2[3] = {100, 110, 120};
    dList *list6 = createListFromArray(arr2, 3);
    removeTail(list6);
    assert(list6->pTail->key == 110 && list6->pTail->pNext == nullptr);
    removeTail(list6);
    assert(list6->pTail->key == 100 && list6->pTail->pNext == nullptr && list6->pHead == list6->pTail);
    removeTail(list6);
    assert(list6->pHead == nullptr && list6->pTail == nullptr);
    dList *emptyList6 = new dList();
    removeTail(emptyList6); // Remove from empty list
    std::cout << "Passed" << std::endl;
    freeList(emptyList6);
    freeList(list6);

    // Test case 7: removeAll /////////////////////////////////////////////////////////////////////
    std::cout << "Test removeAll: ";
    int arr3[3] = {130, 140, 150};
    dList *list7 = createListFromArray(arr3, 3);
    removeAll(list7);
    assert(list7->pHead == nullptr && list7->pTail == nullptr);
    dList *emptyList7 = new dList();
    removeAll(emptyList7); // Remove from empty list
    assert(emptyList7->pHead == nullptr && emptyList7->pTail == nullptr);
    std::cout << "Passed" << std::endl;
    freeList(emptyList7);
    freeList(list7);

    // Test case 8: removeBefore //////////////////////////////////////////////////////////////////////
    std::cout << "Test removeBefore: ";
    int arr4[5] = {160, 170, 180, 190, 200};
    dList *list8 = createListFromArray(arr4, 5);

    // testcase 1
    removeBefore(list8, 180);
    int expectedArr8[4] = {160, 180, 190, 200};
    dList *expectedList8 = createListFromArray(expectedArr8, 4);
    assert(areListsEqual(list8, expectedList8));

    // testcase 2
    removeBefore(list8, 200);
    int expectedArr8_2[3] = {160, 180, 200};
    dList *expectedList8_2 = createListFromArray(expectedArr8_2, 3);
    assert(areListsEqual(list8, expectedList8_2));

    // testcase 3
    removeBefore(list8, 170); // Don't have any element before
    int expectedArr8_2_2[3] = {160, 180, 200};
    dList *expectedList8_2_2 = createListFromArray(expectedArr8_2_2, 3);
    assert(areListsEqual(list8, expectedList8_2_2));

    // free memory
    freeList(expectedList8);
    freeList(expectedList8_2);
    freeList(expectedList8_2_2);
    freeList(list8);
    std::cout << "Passed" << std::endl;

    // Test case 9: remove after ////////////////////////////////////////////////////////////
    std::cout << "Test removeAfter: ";
    int arr5[4] = {220, 230, 240, 250};
    dList *list9 = createListFromArray(arr5, 4);
    // testcase 1
    removeAfter(list9, 220);
    int expectedArr9[3] = {220, 240, 250};
    dList *expectedList9 = createListFromArray(expectedArr9, 3);
    assert(areListsEqual(list9, expectedList9));
    // testcase 2
    removeAfter(list9, 250); // Don't have any element after
    int expectedArr9_2[3] = {220, 240, 250};
    dList *expectedList9_2 = createListFromArray(expectedArr9_2, 3);
    assert(areListsEqual(list9, expectedList9_2));
    // testcase 3
    removeAfter(list9, 240);
    int expectedArr9_3[2] = {220, 240};
    dList *expectedList9_3 = createListFromArray(expectedArr9_3, 2);
    assert(areListsEqual(list9, expectedList9_3));
    // testcase 4
    int arr9_single[1] = {260};
    dList *list9_single = createListFromArray(arr9_single, 1);
    removeAfter(list9_single, 260);
    int expectedArr9_single[1] = {260};
    dList *expectedList9_single = createListFromArray(expectedArr9_single, 1);
    assert(areListsEqual(list9_single, expectedList9_single));
    // testcase 5
    dList *emptyList9 = new dList();
    removeAfter(emptyList9, 270);
    assert(areListsEqual(emptyList9, new dList()));
    // free memory
    freeList(expectedList9);
    freeList(expectedList9_2);
    freeList(expectedList9_3);
    freeList(expectedList9_single);
    freeList(list9);
    freeList(list9_single);
    freeList(emptyList9);
    std::cout << "Passed" << std::endl;

    // // Test case 10: addPos /////////////////////////////////////////////////////////
    std::cout << "Test addPos: ";
    dList *list10 = new dList();
    assert(addPos(list10, 280, 0));
    assert(list10->pHead != nullptr && list10->pHead->key == 280 && list10->pTail->key == 280);
    assert(addPos(list10, 290, 1));
    assert(list10->pHead->key == 280 && list10->pTail->key == 290 && list10->pHead->pNext->key == 290);
    assert(addPos(list10, 300, 1));
    assert(list10->pHead->key == 280 && list10->pTail->key == 290 && list10->pHead->pNext->key == 300);
    assert(list10->pHead->pNext->pNext->key == 290);
    assert(addPos(list10, 310, 3));
    assert(list10->pHead->key == 280 && list10->pTail->key == 310 && list10->pHead->pNext->key == 300);
    assert(list10->pHead->pNext->pNext->key == 290 && list10->pHead->pNext->pNext->pNext->key == 310);
    assert(!addPos(list10, 320, 5));  // Positions out of range
    assert(!addPos(list10, 330, -1)); // Negative position
    // free memory
    freeList(list10);
    std::cout << "Passed" << std::endl;

    // Test case 11: RemovePos /////////////////////////////////////////////////////////
    std::cout << "Test RemovePos: ";
    int arr11[5] = {340, 350, 360, 370, 380};
    dList *list11 = createListFromArray(arr11, 5);
    assert(list11->pHead->key == 340 && list11->pTail->key == 380);
    // testcase 1
    removePos(list11, 340, 0);
    assert(list11->pHead->key == 350 && list11->pTail->key == 380);
    assert(list11->pHead->pNext->key == 360 && list11->pHead->pNext->pNext->key == 370 && list11->pHead->pNext->pNext->pNext->key == 380);
    assert(list11->pHead->pNext->pNext->pNext->pNext == nullptr);
    // testcase 2
    removePos(list11, 370, 2);
    assert(list11->pHead->key == 350 && list11->pTail->key == 380);
    assert(list11->pHead->pNext->key == 360 && list11->pHead->pNext->pNext->key == 380);
    assert(list11->pHead->pNext->pNext->pNext == nullptr);
    // testcase 3
    removePos(list11, 350, 5); // Positions out of range
    assert(list11->pHead->key == 350 && list11->pTail->key == 380);
    assert(list11->pHead->pNext->key == 360 && list11->pHead->pNext->pNext->key == 380);
    assert(list11->pHead->pNext->pNext->pNext == nullptr);
    // free memory
    freeList(list11);
    std::cout << "Passed" << std::endl;

    // Test case 12: addBefore /////////////////////////////////////////////////////////
    std::cout << "Test addBefore: ";
    int arr12[4] = {390, 400, 410, 420};
    dList *list12 = createListFromArray(arr12, 4);
    assert(list12->pHead->key == 390 && list12->pTail->key == 420);
    // testcase 1
    addBefore(list12, 380, 400);
    int arr12_1[5] = {390, 380, 400, 410, 420};
    dList *expectedList12_1 = createListFromArray(arr12_1, 5);
    assert(areListsEqual(list12, expectedList12_1));
    // testcase 2
    addBefore(list12, 370, 390);
    int arr12_2[6] = {370, 390, 380, 400, 410, 420};
    dList *expectedList12_2 = createListFromArray(arr12_2, 6);
    assert(areListsEqual(list12, expectedList12_2));
    // testcase 3
    addBefore(list12, 360, 350); // Don't have any element before
    int arr12_3[6] = {370, 390, 380, 400, 410, 420};
    dList *expectedList12_3 = createListFromArray(arr12_3, 6);
    assert(areListsEqual(list12, expectedList12_3));
    // free memory
    freeList(list12);
    freeList(expectedList12_1);
    freeList(expectedList12_2);
    freeList(expectedList12_3);
    std::cout << "Passed" << std::endl;

    // Test case 13: addAfter /////////////////////////////////////////////////////////
    std::cout << "Test addAfter: ";
    int arr13[4] = {430, 440, 450, 460};
    dList *list13 = createListFromArray(arr13, 4);
    assert(list13->pHead->key == 430 && list13->pTail->key == 460);
    // testcase 1
    addAfter(list13, 470, 440);
    int arr13_1[5] = {430, 440, 470, 450, 460};
    dList *expectedList13_1 = createListFromArray(arr13_1, 5);
    assert(areListsEqual(list13, expectedList13_1));
    // testcase 2
    addAfter(list13, 480, 460);
    int arr13_2[6] = {430, 440, 470, 450, 460, 480};
    dList *expectedList13_2 = createListFromArray(arr13_2, 6);
    assert(areListsEqual(list13, expectedList13_2));
    // testcase 3
    addAfter(list13, 490, 200); // Don't have any element after
    int arr13_3[6] = {430, 440, 470, 450, 460, 480};
    dList *expectedList13_3 = createListFromArray(arr13_3, 6);
    assert(areListsEqual(list13, expectedList13_3));
    // free memory
    freeList(expectedList13_1);
    freeList(expectedList13_2);
    freeList(expectedList13_3);
    freeList(list13);
    std::cout << "Passed" << std::endl;

    // Test case 14: printList /////////////////////////////////////////////////////////
    std::cout << "Test printList: "; // Don't need to assert anything
    std::cout << "Passed" << std::endl;

    // Test case 15: countElements /////////////////////////////////////////////////////////
    std::cout << "Test countElements: ";
    // Test case 1
    int arr15[5] = {500, 510, 520, 530, 540};
    dList *list15 = createListFromArray(arr15, 5);
    assert(countElements(list15) == 5);
    // Test case 2
    int arr15_2[3] = {550, 560, 570};
    dList *list15_2 = createListFromArray(arr15_2, 3);
    assert(countElements(list15_2) == 3);
    // Test case 3
    int arr15_3[1] = {580};
    dList *list15_3 = createListFromArray(arr15_3, 1);
    assert(countElements(list15_3) == 1);
    // Test case 4
    dList *emptyList15 = new dList();
    assert(countElements(emptyList15) == 0);
    // free memory
    freeList(list15);
    freeList(list15_2);
    freeList(list15_3);
    freeList(emptyList15);
    std::cout << "Passed" << std::endl;

    // Test case 16: reverseList /////////////////////////////////////////////////////////
    std::cout << "Test reverseList: ";
    // Test case 1
    int arr16[5] = {590, 600, 610, 620, 630};
    dList *list16 = createListFromArray(arr16, 5);
    dList *reversedList16 = reverseList(list16);
    int expectedArr16[5] = {630, 620, 610, 600, 590};
    dList *expectedList16 = createListFromArray(expectedArr16, 5);
    assert(areListsEqual(reversedList16, expectedList16));
    // Test case 2
    int arr16_2[3] = {640, 650, 660};
    dList *list16_2 = createListFromArray(arr16_2, 3);
    dList *reversedList16_2 = reverseList(list16_2);
    int expectedArr16_2[3] = {660, 650, 640};
    dList *expectedList16_2 = createListFromArray(expectedArr16_2, 3);
    assert(areListsEqual(reversedList16_2, expectedList16_2));
    // Test case 3
    int arr16_3[1] = {670};
    dList *list16_3 = createListFromArray(arr16_3, 1);
    dList *reversedList16_3 = reverseList(list16_3);
    int expectedArr16_3[1] = {670};
    dList *expectedList16_3 = createListFromArray(expectedArr16_3, 1);
    assert(areListsEqual(reversedList16_3, expectedList16_3));
    // Test case 4
    dList *emptyList16 = new dList();
    dList *reversedList16_4 = reverseList(emptyList16);
    assert(reversedList16_4->pHead == nullptr && reversedList16_4->pTail == nullptr);
    // free memory
    freeList(expectedList16);
    freeList(expectedList16_2);
    freeList(expectedList16_3);
    freeList(reversedList16);
    freeList(reversedList16_2);
    freeList(reversedList16_3);
    freeList(reversedList16_4);
    freeList(list16);
    freeList(list16_2);
    freeList(list16_3);
    freeList(emptyList16);
    std::cout << "Passed" << std::endl;

    // Test case 17: removeDuplicate /////////////////////////////////////////////////////////
    std::cout << "Test removeDuplicate: ";
    // Test case 1
    int arr17[6] = {680, 690, 690, 700, 710, 710};
    dList *list17 = createListFromArray(arr17, 6);
    removeDuplicate(list17);
    int expectedArr17[4] = {680, 690, 700, 710};
    dList *expectedList17 = createListFromArray(expectedArr17, 4);
    assert(areListsEqual(list17, expectedList17));
    // Test case 2
    int arr17_2[5] = {720, 730, 740, 740, 740};
    dList *list17_2 = createListFromArray(arr17_2, 5);
    removeDuplicate(list17_2);
    int expectedArr17_2[3] = {720, 730, 740};
    dList *expectedList17_2 = createListFromArray(expectedArr17_2, 3);
    assert(areListsEqual(list17_2, expectedList17_2));
    // Test case 3
    int arr17_3[4] = {750, 760, 760, 770};
    dList *list17_3 = createListFromArray(arr17_3, 4);
    removeDuplicate(list17_3);
    int expectedArr17_3[3] = {750, 760, 770};
    dList *expectedList17_3 = createListFromArray(expectedArr17_3, 3);
    assert(areListsEqual(list17_3, expectedList17_3));
    // Test case 4
    int arr17_4[2] = {780, 780};
    dList *list17_4 = createListFromArray(arr17_4, 2);
    removeDuplicate(list17_4);
    int expectedArr17_4[1] = {780};
    dList *expectedList17_4 = createListFromArray(expectedArr17_4, 1);
    assert(areListsEqual(list17_4, expectedList17_4));
    // Test case 5
    int arr17_5[1] = {790};
    dList *list17_5 = createListFromArray(arr17_5, 1);
    removeDuplicate(list17_5);
    int expectedArr17_5[1] = {790};
    dList *expectedList17_5 = createListFromArray(expectedArr17_5, 1);
    assert(areListsEqual(list17_5, expectedList17_5));
    // Test case 6
    dList *emptyList17 = new dList();
    removeDuplicate(emptyList17);
    assert(emptyList17->pHead == nullptr && emptyList17->pTail == nullptr);
    // free memory
    freeList(expectedList17);
    freeList(expectedList17_2);
    freeList(expectedList17_3);
    freeList(expectedList17_4);
    freeList(expectedList17_5);
    freeList(list17);
    freeList(list17_2);
    freeList(list17_3);
    freeList(list17_4);
    freeList(list17_5);
    freeList(emptyList17);
    std::cout << "Passed" << std::endl;

    // Test case 18: removeElement /////////////////////////////////////////////////////////
    std::cout << "Test removeElement: ";
    // Test case 1
    int arr18[5] = {800, 810, 820, 830, 840};
    dList *list18 = createListFromArray(arr18, 5);
    assert(removeElement(list18, 820));
    int expectedArr18[4] = {800, 810, 830, 840};
    dList *expectedList18 = createListFromArray(expectedArr18, 4);
    assert(areListsEqual(list18, expectedList18));
    // Test case 2
    int arr18_2[3] = {850, 860, 870};
    dList *list18_2 = createListFromArray(arr18_2, 3);
    assert(removeElement(list18_2, 850));
    int expectedArr18_2[2] = {860, 870};
    dList *expectedList18_2 = createListFromArray(expectedArr18_2, 2);
    assert(areListsEqual(list18_2, expectedList18_2));
    // Test case 3
    int arr18_3[4] = {880, 890, 900, 910};
    dList *list18_3 = createListFromArray(arr18_3, 4);
    assert(removeElement(list18_3, 910));
    int expectedArr18_3[3] = {880, 890, 900};
    dList *expectedList18_3 = createListFromArray(expectedArr18_3, 3);
    assert(areListsEqual(list18_3, expectedList18_3));
    // Test case 4
    int arr18_4[2] = {920, 930};
    dList *list18_4 = createListFromArray(arr18_4, 2);
    assert(removeElement(list18_4, 920));
    int expectedArr18_4[1] = {930};
    dList *expectedList18_4 = createListFromArray(expectedArr18_4, 1);
    assert(areListsEqual(list18_4, expectedList18_4));
    // Test case 5
    int arr18_5[1] = {940};
    dList *list18_5 = createListFromArray(arr18_5, 1);
    assert(removeElement(list18_5, 940));
    int *expectedArr18_5 = nullptr; // Use a null pointer to represent an empty array
    dList *expectedList18_5 = createListFromArray(expectedArr18_5, 0);
    assert(areListsEqual(list18_5, expectedList18_5));
    // Test case 6
    dList *emptyList18 = new dList();
    assert(!removeElement(emptyList18, 950)); // Remove from empty list
    assert(emptyList18->pHead == nullptr && emptyList18->pTail == nullptr);
    // free memory
    freeList(expectedList18);
    freeList(expectedList18_2);
    freeList(expectedList18_3);
    freeList(expectedList18_4);
    freeList(expectedList18_5);
    freeList(list18);
    freeList(list18_2);
    freeList(list18_3);
    freeList(list18_4);
    freeList(list18_5);
    freeList(emptyList18);
    std::cout << "Passed" << std::endl;
    std::cout << "--- End running test cases ---" << std::endl;
    return 0;
}