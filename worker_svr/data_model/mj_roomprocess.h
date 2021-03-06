#ifndef MJ_ROOMPROCESS_H
#define MJ_ROOMPROCESS_H

#include "room_data_object.h"
#include "user_data_object.h"

#include "redis_cli/redis_support.h"

class mj_roomprocess
{
    /**
     * @brief 根据card获取当前玩家可以吃的所有组合,存入result中
     * @param obj
     * @param card
     * @param result
     */
    void get_cchi_list(user_data_object &obj, char card, vector<string> &result);

public:
    mj_roomprocess(string &room_name);
    mj_roomprocess(const mj_roomprocess&) = delete;
    ~mj_roomprocess();

    /**
     * @brief 胡杠碰吃策略 enum
     */
    enum hgpc_plocy {
        P_Hu    = 1,
        P_Gang  = 2,
        P_Peng  = 4,
        P_Chi   = 8
    };

    void load();
    void store();

    /**
     *  @brief:     开始一局游戏,
     *  @users:     IN  四位玩家, 0下标玩家是庄家
     *  @roomdata:  OUT 房间数据
     *  @userdatas: OUT 玩家数据
     *  ret:        房间号ID
    */
    static string new_game(vector<std::string> &users, room_data_object &roomdata, vector<user_data_object> &userdatas);

    // fapai
    bool fapai(int &cur_id, char &card);

    // chupai
    bool chupai(const string &uid, char card);

    // hint
    /***
     *  @uid: IN. 出牌的玩家
     *  @card: IN. 玩家所出的牌
     *  @h: OUT. 分析其他玩家的可胡牌结果
     *  @g: OUT.
     *  @p: OUT.
     *  @c: OUT.
     */
    void hint_hgpc(const string &uid, char card, vector<int> &h, vector<int> &g, vector<int> &p,
                   vector<vector<string>> &c);

    /**
     * @brief 分析uid玩家的胡杠碰吃, 并返回结果
     * @param uid
     * @param h
     * @param g
     * @param p
     * @param c
     */
    void analysis_hgpc(const string &uid, string &h, string &g, string &p, vector<string> &c);

    //
    string chi(const string &uid, const string &c);

    //
    string peng(const string &uid, const char p);

    //
    string gang(const string &uid, const char g);

    //
    string agang(const string &uid, const char g);

    //
    string zgang(const string &uid, const char g);

    //
    string hu(const string &uid, const char h);

    //
    void get_user_hupaicards(const string &uid, string &cards, char &h);


private:
    std::string room_id;
    room_data_object room;
    std::vector<user_data_object> players;
};

#endif // MJ_ROOMPROCESS_H
