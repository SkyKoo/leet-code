/*
 * @lc app=leetcode.cn id=432 lang=cpp
 * @lcpr version=30113
 *
 * [432] 全 O(1) 的数据结构
 *
 * https://leetcode.cn/problems/all-oone-data-structure/description/
 *
 * algorithms
 * Hard (46.65%)
 * Likes:    314
 * Dislikes: 0
 * Total Accepted:    29.8K
 * Total Submissions: 63.8K
 * Testcase Example:  '["AllOne","inc","inc","getMaxKey","getMinKey","inc","getMaxKey","getMinKey"]\n' +
  '[[],["hello"],["hello"],[],[],["leet"],[],[]]'
 *
 * 请你设计一个用于存储字符串计数的数据结构，并能够返回计数最小和最大的字符串。
 * 
 * 实现 AllOne 类：
 * 
 * 
 * AllOne() 初始化数据结构的对象。
 * inc(String key) 字符串 key 的计数增加 1 。如果数据结构中尚不存在 key ，那么插入计数为 1 的 key 。
 * dec(String key) 字符串 key 的计数减少 1 。如果 key 的计数在减少后为 0 ，那么需要将这个 key
 * 从数据结构中删除。测试用例保证：在减少计数前，key 存在于数据结构中。
 * getMaxKey() 返回任意一个计数最大的字符串。如果没有元素存在，返回一个空字符串 "" 。
 * getMinKey() 返回任意一个计数最小的字符串。如果没有元素存在，返回一个空字符串 "" 。
 * 
 * 
 * 注意：每个函数都应当满足 O(1) 平均时间复杂度。
 * 
 * 
 * 
 * 示例：
 * 
 * 输入
 * ["AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc", "getMaxKey",
 * "getMinKey"]
 * [[], ["hello"], ["hello"], [], [], ["leet"], [], []]
 * 输出
 * [null, null, null, "hello", "hello", null, "hello", "leet"]
 * 
 * 解释
 * AllOne allOne = new AllOne();
 * allOne.inc("hello");
 * allOne.inc("hello");
 * allOne.getMaxKey(); // 返回 "hello"
 * allOne.getMinKey(); // 返回 "hello"
 * allOne.inc("leet");
 * allOne.getMaxKey(); // 返回 "hello"
 * allOne.getMinKey(); // 返回 "leet"
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= key.length <= 10
 * key 由小写英文字母组成
 * 测试用例保证：在每次调用 dec 时，数据结构中总存在 key
 * 最多调用 inc、dec、getMaxKey 和 getMinKey 方法 5 * 10^4 次
 * 
 * 
 */


// @lcpr-template-start
using namespace std;
#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
// @lcpr-template-end
// @lc code=start
class AllOne {
public:
    AllOne() {
    }
    
    void inc(string key) {
        auto it = data.find(key);
        if (it == data.end()) {
            // key 不存在，插入 key 个数 1
            if (!top.empty()) {
                // top 不为空，判断第一个集合 的 个数 值
                if (top.begin()->second == 1) {
                    // 个数值 是 1 正好 插入 key
                    top.begin()->first.insert(key);
                    data[key] = top.begin();
                } else {
                    // 个数值 不是 1，创建一个 个数值 是 1 的数据及，并把 key 插入进取
                    unordered_set<string> s;
                    s.insert(key);
                    top.push_front(make_pair(s, 1));
                    // 数据集要再插入到 data 中
                    data[key] = top.begin();
                }
            } else {
                // top 是空，插入第一个数据集，其个数是 1
                unordered_set<string> s;
                s.insert(key);
                top.push_front(make_pair(s, 1));
                // 数据集插入到 data 中
                data[key] = top.begin();
            }
        } else {
            // key 存在，由于 个数 需要 +1，需要将其移动数据集
            // 先找到数据集 iterator cur，判断他后面的数据集 个数 是否是当前数据集 个数 + 1
            auto cur = it->second;
            auto nxt = next(cur);
            if (nxt == top.end() || nxt->second != cur->second + 1) {
                unordered_set<string> s;
                s.insert(key);
                auto pos = top.insert(nxt, make_pair(s, cur->second + 1));
                data[key] = pos;
            } else {
                // nxt 的数据集 个数 正是当前数据集 个数 + 1，直接插入到 nxt 数据集中
                nxt->first.insert(key);
                data[key] = nxt;
            }
            // 原有数据集把 key 去掉
            cur->first.erase(key);
            // 如果 cur 数据集 空了，则把数据集也删掉
            if (cur->first.empty()) {
                top.erase(cur);
            }
        }
        // print();
    }
    
    void dec(string key) {
        auto it = data.find(key);
        // 判断 key 是否存在，不存在则什么都不做
        if (it != data.end()) {
            // cur 是 key 所在的数据集
            auto cur = it->second;
            auto pre = prev(cur);
            if (cur->second > 1) {
                // cur 数据集 个数不是1 的情况 还要判断是否存在 pre 数据集
                if (pre != top.end()) {
                    if (pre->second != cur->second - 1) {
                        // pre 数据集 存在，但是 个数 不对，需要创建一个新的数据集
                        unordered_set<string> s;
                        s.insert(key);
                        auto pos = top.insert(cur, make_pair(s, cur->second - 1));
                        data[key] = pos;
                    } else {
                        // pre 数据集 存在，且 个数 对，直接插入到前一个数据集
                        pre->first.insert(key);
                        data[key] = pre;
                    }
                } else {
                    // pre 数据集不存在，则创建一个新的数据集 插入到 cur 前面
                    unordered_set<string> s;
                    s.insert(key);
                    auto pos = top.insert(cur, make_pair(s, cur->second - 1));
                    data[key] = pos;
                }
                // 原有数据集删掉 key
                cur->first.erase(key);
                // 如果 key 所在的数据集 空了，则把数据集也删掉
                if (cur->first.empty()) {
                    top.erase(cur);
                }
            } else {
                // cur 数据集 个数 是 1， 说明当前 key 只出现一次，则直接删掉 key
                cur->first.erase(key);
                // 如果 key 所在的数据集 空了，则把数据集也删掉
                if (cur->first.empty()) {
                    top.erase(cur);
                }
                data.erase(key);
            }
        }
        // print();
    }
    
    string getMaxKey() {
        return top.empty() ? "" : *(top.back().first.begin());
    }
    
    string getMinKey() {
        return top.empty() ? "" : *(top.front().first.begin());
    }

    void print() {
        cout << "----------" << endl;
        for (auto t : top) {
            cout << "No." << t.second << endl;
            for (auto s : t.first) {
                cout << s << endl;
            }
        }
    }
private:
    /*
     * | str1 | str2 | str3 | ... | strN |
     * |  |   |  |   |   |  | ... |  |   |
     * |  V   |  V   |   V  | ... |  V   |
     * | lstA | lstB | lstA | ... | lstB |
     * |  |   |  |   |   |  | ... |  |   |
     * |  V   |  V   |   V  | ... |  V   |
     * | setA | setB | setA | ... | setB |
     */
    unordered_map<string, list<pair<unordered_set<string>, int>>::iterator> data;
    list<pair<unordered_set<string>, int>> top; 
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
// @lc code=end



