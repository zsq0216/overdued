# PJ1文档
> 21302010069 钟思祺
## 设计细节
### 红黑树
#### COLOR
枚举类型数据，包含RED 和 BLACK，用于标识节点的颜色
#### RB_node
* 结点类，封装了单词元素的属性和红黑树节点的属性
* 单词属性：key(Word),pos(Part-Of-Speech),frq(Frequency)
* 结点属性：左子节点left，右子节点right，父节点p，颜色color
#### RB_TREE
##### root
* 根节点
##### nil
* 空节点，红黑树中所有的nullptr都可以用它来替代，可大大节省空间
##### 左旋left_rotate()
* 假设在x上做左旋，x的右节点为y，x的父节点为p。
* y接替x成为p的子节点，x成为y的左子节点，同时y原来的左子节点成为x的右子节点。
##### 右旋right_rotate()
* 同左旋，方向相反。
##### insert_fixup()
* 对结点重新着色并旋转，以保持红黑树的性质
* 需要变动的有三种情况：
  * case1: uncle is red -> change color
  * case2: father has the same side with me -> contrary side rotate
  * case3: different side -> pre_rotate & rotate
* 最后保证根节点是黑的
##### delete_fixup()
* 对结点重新着色并旋转，以保持红黑树的性质
* 当红红相连时需要变动，有四种情况：
  * case1: x的兄弟结点是红的 -> 对x.parent做左旋 -> 归约到case2 or case3 or case4.
  * case2: x的兄弟结点w是黑色的，而且w的两个子结点都是黑色的 -> 将w改为红色，把x.p作为新结点x来重复循环
  * case3: w是黑色的，w的左孩子是红色，右孩子是黑色 -> 交换w和w.left的颜色，对w右旋 -> 归约到case4
  * case4: w是黑色且w.right是红色 -> 把w改成x.p的颜色，把x.p改成黑色，再对x.p做一次左旋。终止循环
##### minimum()
* 返回以x为子树的key最小的结点。
* 用于在delete中找后继。
##### in_traversal()
* 递归版本的中序遍历。
##### Insert()
* 插入在合适的叶结点。过程中需要两个指针记录当前结点和当前结点的父节点，方便为新节点建立父子关系。
* 如果已经存在就放弃插入，并显示冲突信息
* 插入新结点后调用insert_fixup(z)
##### Delete()
* 先找到那个要被删除的结点x。要是不在树中，就显示丢失信息，并放弃删除
* 看x是否左右儿子都存在。若都存在，删x的后继；若不都存在，删x本身
* 若删除的结点是黑色，那意味着红黑树的性质被破坏，需要调用delete_fixup()恢复性质
##### Update()
* 在Insert()基础上做小改动：如果树中已存在此单词，就将它的value更新。
##### Search()
* 利用二叉搜索树的性质迭代查找键为key的结点，输出value。
##### Dump()
* 调用in_traversal(root),从树的根节点开始中序遍历，显示树中的所有键值对。
### B树
##### word
* 单词结构
* key:Word
* pos:Part-Of-Speech
* frq:Frequency
#### B_Tree
##### B_Node
* vector<word> nodeKey：关键字数组
* vector<B_Node *> nodeChild：子结点数组
* nodePlace：用于记录某元素的位置
* t：最小度数,用宏定义MINDEGREE来初始化
* nodeKey.size()可表示结点中关键词的数量
* nodeChild.empty()可表示是否为叶节点
##### SplitChild()
* B树的性质要求结点关键字数最多不能超过2t-1
* 当结点x中含有2t-1个关键字时，新增一个结点y,将x的中间节点上升到父节点中，再把t-1个关键字和t个子结点一一赋给y。使得x,y均有t-1个关键字和t个子结点
* 具体是用vector的push_back,pop_back,insert来完成数组的变动
##### Insert_notfull()
* 辅助插入的递归过程，将关键字插入底层结点x.
* Insert(),Insert_notfull()都保证了x非满：一旦满了，就执行SplitChild()分裂结点。
##### search()
* 用二叉搜索树的性质找到关键字，返回它的位置nodePlace
##### predecessor() successor()
* 非完整，只适用于向下找前驱后继
* 返回关键字的位置nodePlace
* 服务于Delete()
##### minimum() maximum()
* 返回最小/最大关键字所在的结点B_Node
* 服务于predecessor() successor()
##### combine()
* B树的性质要求结点关键字数最少为t-1(root除外)
* 因此当违背该性质时，将z.k[i]下拉与z.c[i],z.c[i+1]形成一个新的结点
* 具体是用vector的push_back,erase实现数组的变动
##### in_traversal()
* 递归版本的中序遍历。
##### Insert()
* 根结点和其他结点的性质不太一样，允许关键字数量小于t-1.所以在Insert里单独处理根结点，并保证根结点关键字数量小于2t-1
* 调用Insert_notfull()，插入关键字
* 如果已经存在就放弃插入，并显示冲突信息
##### Delete()
* 充分考虑各种情况：
  * 如果关键字在叶结点中，由于自上而下递归调用已经用combine()保证了结点数>t-1，直接删删除关键字即可
  * 如果在内部结点，预看左右子节点，选一个富余的子结点，若左孩子富余就用前驱替代当前关键字，删除前驱；若右孩子富余就由后继替代当前关键字，删除后继。
  * 若在中间结点且左右孩子都不富余，combine后再递归调用Delete
  * 如果关键字不再当前内部结点中，则递归调用子结点向下寻找待删除的关键字。递归之前要先预看子结点，预防关键字数量过少：
    * 若x.c[i]只含t-1个关键字且它的一个相邻兄弟至少包含t个，则将x的一个关键字降到x.c[i]中，再从兄弟里升一个关键字到x中
    * 若都兄弟都只含t-1个关键字，选择其中一个与x.c[i]合并
##### Update()
* 调用search()找关键字，若找到了就更新单词
* 若没找到，则调用Insert()插入单词
##### Dump()
* 调用in_traversal(root),从树的根节点开始中序遍历，显示树中的所有键值对。

## 关于本次PJ的思考
* 实现思路多次用到归约思想。比如红黑树的insert_fixup,delete_fixup，都是先确定简单情况的解决方法，再将复杂情况向简单情况转化。
* B树的结点是用vector实现的，调用库中的插入删除操作和size()统计结点中关键字个数，能减少改动关键字个数的麻烦。
* B树的实现参考了文章<https://www.cnblogs.com/yxsrt/p/12201655.html>