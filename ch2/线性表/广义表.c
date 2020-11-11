typedef int ElementType;
typedef struct GNode *GList;

// 在线性表中，n个元素都是基本的单元素
// 在广义表里面，每个元素可以是单元素，也可以是广义表
struct GNode
{
    int Tag;
    union {
        ElementType Data;
        GList SubList;
    } URegion;

    GList Next;
}