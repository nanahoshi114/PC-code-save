#include <iostream>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <array>
enum inst_type {
    SLACK_OFF,
    MOVE,
    SWAP,
    MIRROR,
    REPLACE,
    ACTIVATE,
    TRIGGER
};
std::unordered_map<std::string, inst_type> command_type {
    {"SLACKOFF", SLACK_OFF},
    {"MOVE", MOVE},
    {"SWAP", SWAP},
    {"MIRROR", MIRROR},
    {"REPLACE", REPLACE},
    {"ACTIVATE", ACTIVATE},
    {"TRIGGER", TRIGGER}
};
constexpr const char *robot_direction[2] = {"left", "right"};
class Instruction;
struct Robot;
class Instruction : public std::enable_shared_from_this<Instruction> {
protected:
    inst_type type;
    static std::vector<Robot> *all_robot;
    bool mirror_tag;
    bool is_trigger;
public:
    static int max_output, count;
    inline static void set_robot_array(std::vector<Robot> *all_robot_) {
        all_robot = all_robot_;
    }
    inline static void check_if_over() {
        ++count;
        if (count == max_output) {
            std::exit(0);
        }
    }
    inline virtual void mirror() {
        mirror_tag = !mirror_tag;
    }
    inline virtual std::shared_ptr<Instruction> copy() const = 0;
    Instruction() : mirror_tag(), is_trigger() {}
    inline void set_trigger() {
        is_trigger = true;
    }
    inline auto get_type() const { return type; }
    inline virtual void action(int rb_num) = 0;
    virtual ~Instruction() = default;
};
int Instruction::max_output, Instruction::count;
std::vector<Robot> *Instruction::all_robot;
struct Robot {
    std::vector<std::shared_ptr<Instruction>> insts;
    int id;
    std::array<int, 2> hand_id;
    inline void check_trigger(Robot &r_rbt, inst_type type, bool is_trigger);
    inline void activate() {
        for (const auto &cmd : insts) {
            cmd->action(id);
        }
    }
};
class inst_slackoff : public Instruction {
public:
    inst_slackoff() : Instruction() {
        type = SLACK_OFF;
    }
    inline std::shared_ptr<Instruction> copy() const override {
        return std::make_shared<inst_slackoff>();
    }
    inline void action(int rbt_id) override {
        auto &self = all_robot->operator[](rbt_id);
        std::cout << "Robot " << rbt_id << " slacks off.\n";
        check_if_over();
        self.check_trigger(all_robot->operator[](self.hand_id[1]), type, is_trigger);
    }
};
class inst_move : public Instruction {
    bool hand;
    int dis;
public:
    inst_move(bool hand, int dis) : Instruction(), hand(hand), dis(dis) {
        type = MOVE;
    }
    inline std::shared_ptr<Instruction> copy() const override {
        auto p = std::make_shared<inst_move>(hand, dis);
        p->mirror_tag = mirror_tag;
        return p;
    }
    inline void action(int rbt_id) override {
        bool f = hand ^ mirror_tag;
        auto &self = all_robot->operator[](rbt_id);
        std::cout << "Robot " 
                  << rbt_id
                  << " moves its " 
                  << robot_direction[f] 
                  << " hand towards Robot " 
                  << (self.hand_id[f] + dis) % all_robot->size()
                  << ".\n";
        check_if_over();
        self.hand_id[f] = (self.hand_id[f] + dis) % all_robot->size();
        self.check_trigger(all_robot->operator[](self.hand_id[1]), type, is_trigger);
    }
};
class inst_swap : public Instruction {
    bool hand;
    int x, y;
public:
    inst_swap(bool hand, int x, int y) : Instruction(), hand(hand), x(x), y(y) {
        type = SWAP;
    }
    inline std::shared_ptr<Instruction> copy() const override {
        auto p = std::make_shared<inst_swap>(hand, x, y);
        p->mirror_tag = mirror_tag;
        return p;
    }
    inline void action(int rbt_id) override {
        bool f = hand ^ mirror_tag;
        auto &self = all_robot->operator[](rbt_id), 
             &other = all_robot->operator[](self.hand_id[f]);
        std::cout << "Robot "
                  << rbt_id
                  << " swaps a line of command with Robot "
                  << self.hand_id[f]
                  << ".\n";
        check_if_over();
        std::swap(self.insts[y], other.insts[x]);
        self.check_trigger(all_robot->operator[](self.hand_id[1]), type, is_trigger);
    }
};
class inst_mirror : public Instruction {
    bool hand;
    int x;
public:
    inst_mirror(bool hand, int x) : Instruction(), hand(hand), x(x) {
        type = MIRROR;
    }
    inline std::shared_ptr<Instruction> copy() const override {
        auto p = std::make_shared<inst_mirror>(hand, x);
        p->mirror_tag = mirror_tag;
        return p;
    }
    inline void action(int rbt_id) override {
        bool f = hand ^ mirror_tag;
        auto &self = all_robot->operator[](rbt_id),
             &other = all_robot->operator[](self.hand_id[f]);
        std::cout << "Robot "
                  << rbt_id
                  << " modifies a line of command of Robot "
                  << self.hand_id[f]
                  << ".\n";
        check_if_over();
        other.insts[x]->mirror();
        self.check_trigger(all_robot->operator[](self.hand_id[1]), type, is_trigger);
    }
};
class inst_replace : public Instruction {
    bool hand;
    int x;
    std::shared_ptr<Instruction> cmd;
public:
    inst_replace(bool hand, int x, const std::shared_ptr<Instruction> &cmd) : 
    Instruction(), hand(hand), x(x), cmd(cmd) {
        type = REPLACE;
    }
    inline std::shared_ptr<Instruction> copy() const override {
        auto p = std::make_shared<inst_replace>(hand, x, cmd);
        p->mirror_tag = mirror_tag;
        return p;
    }
    inline void action(int rbt_id) override {
        bool f = hand ^ mirror_tag;
        auto &self = all_robot->operator[](rbt_id),
             &other = all_robot->operator[](self.hand_id[f]);
        std::cout << "Robot "
                  << rbt_id
                  << " replaces a line of command of Robot "
                  << self.hand_id[f]
                  << ".\n";
        check_if_over();
        auto t = shared_from_this();
        other.insts[x] = cmd->copy();
        self.check_trigger(all_robot->operator[](self.hand_id[1]), type, is_trigger);
    }
};
class inst_activate : public Instruction {
    bool hand;
public:
    inst_activate(bool hand) : Instruction(), hand(hand) {
        type = ACTIVATE;
    }
    inline std::shared_ptr<Instruction> copy() const override {
        auto p = std::make_shared<inst_activate>(hand);
        p->mirror_tag = mirror_tag;
        return p;
    }
    inline void action(int rbt_id) override {
        bool f = hand ^ mirror_tag;
        auto &self = all_robot->operator[](rbt_id),
             &other = all_robot->operator[](self.hand_id[f]);
        std::cout << "Robot "
                  << rbt_id
                  << " activates Robot "
                  << self.hand_id[f]
                  << ".\n";
        check_if_over();
        auto t = shared_from_this();
        other.activate();
        self.check_trigger(all_robot->operator[](self.hand_id[1]), type, is_trigger);
    }
};
class inst_trigger : public Instruction {
    inst_type cmd_name;
    std::shared_ptr<Instruction> cmd;
public:
    inst_trigger(inst_type name, const std::shared_ptr<Instruction> &cmd) : 
    Instruction(), cmd_name(name), cmd(cmd) {
        type = TRIGGER;
        cmd->set_trigger();
    }
    inline std::shared_ptr<Instruction> copy() const override {
        return std::make_shared<inst_trigger>(cmd_name, cmd->copy());
    }
    inline void mirror() override {
        cmd->mirror();
    }
    inline auto get_cmd_name() const { return cmd_name; }
    inline void action(int rbt_id) override { }
    inline void triggered_action(int rbt_id) {
        cmd->action(rbt_id);
    }
};
inline void Robot::check_trigger(Robot &r_rbt, inst_type type, bool is_trigger) {
    if (r_rbt.id == id) {
        return ;
    }
    for (const auto &cmd : r_rbt.insts) {
        if (cmd->get_type() == TRIGGER) {
            auto tri_cmd = std::static_pointer_cast<inst_trigger>(cmd);
            if (tri_cmd->get_cmd_name() == type || (is_trigger && tri_cmd->get_cmd_name() == TRIGGER)) {
                tri_cmd->triggered_action(r_rbt.id);
                break;
            }
        }
    }
}
std::shared_ptr<Instruction> input_cmd() {
    std::string type;
    std::cin >> type;
    if (type == "SLACKOFF") {
        return std::make_shared<inst_slackoff>();
    } else if (type == "MOVE") {
        bool h; int z;
        std::cin >> h >> z;
        return std::make_shared<inst_move>(h, z);
    } else if (type == "SWAP") {
        bool h;
        int x, y;
        std::cin >> h >> x >> y;
        return std::make_shared<inst_swap>(h, x - 1, y - 1);
    } else if (type == "MIRROR") {
        bool h; int x;
        std::cin >> h >> x;
        return std::make_shared<inst_mirror>(h, x - 1);
    } else if (type == "REPLACE") {
        bool h; int x;
        std::cin >> h >> x;
        return std::make_shared<inst_replace>(h, x - 1, input_cmd());
    } else if (type == "ACTIVATE") {
        bool h;
        std::cin >> h;
        return std::make_shared<inst_activate>(h);
    } else if (type == "TRIGGER") {
        std::string name;
        std::cin >> name;
        name.pop_back();
        return std::make_shared<inst_trigger>(command_type[name], input_cmd());
    }
    return {};
}
int main() { 
    std::cin.tie(nullptr)->sync_with_stdio(false); std::cout.tie(nullptr);
    int n, m;
    std::cin >> n >> m >> Instruction::max_output;
    std::vector<Robot> robot(n);
    Instruction::set_robot_array(&robot);
    for (int i = 0; i < n; ++i) {
        std::cin >> robot[i].hand_id[0] >> robot[i].hand_id[1];
        robot[i].id = i;
        for (int j = 0; j < m; ++j) {
            robot[i].insts.push_back(input_cmd());
        }
    }
    for (int i = 0; ; ++i) {
        robot[i % n].activate();
    }
}