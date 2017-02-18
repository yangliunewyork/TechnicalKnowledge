//insert(p), delete(p1, p2), highlight(p1, p2)，redo/undo, save/load update, search
//text editor需要insert，remove，highlight，需要想办法去index每次插入的object，原po说的interval tree应该就是index的方式吧。
//关键点在于text打算怎么存
//store highlight?
//他要求三天后再load这个text,需要可以undo三天前的操作. save的时候 保存成json/xml类型之类的 把之前的操作也一起存下来

struct textNode{
    string s;
    int index;
};


class RopeNode {
public:
  RopeNode();
  JSON Serialize();
};

class Rope {
public:
  Rope();
  JSON Serialize();
};
// Here TextEditor is the receivor
class TextEditor{
public:
  TextEditor();
  void Insert(std::size_t pos);
  void Delete(std::size_t from, std::size_t to);
  void Highlight(std::size_t from, std::size_t to);
  void DeleteHighlight(std::size_t from, std::size_t to);
  std::size_t Search(const std::string);
  void Save(const std::string & file_path);
  void Load(const std::string & file_path);
private:
  Rope m_rope;
};
typedef std::shared_ptr<TextEditor> TextEditorPtr;

// The command interface
class ICommand {
public:
  ICommand(){}
  ~ICommand(){}
  virtual void Execute() = 0;
  virtual void Undo() = 0;
  virtual void Redo() = 0;
};
typedef std::shared_ptr<ICommand> ICommandPtr;

// The concrete command 
class HighlightCommand : public ICommand {
public:
  HighlightCommand(const TextEditorPtr & editor,std::size_t from, std::size_t to)
    : m_text_editor(editor),m_from(from),m_to(to){}
  void Execute() {m_text_editor->Highlight(m_from,m_to);}
  void Redo() {m_text_editor->Highlight(m_from,m_to);}
  void Undo() {m_text_editor->DeleteHighlight(m_from,m_to);}
private:
  TextEditorPtr m_text_editor;
  std::size_t m_from;
  std::size_t m_to;
};


class CommandManager {
public:
  CommandManager(){}
  void ExecuteCommand(const ICommandPtr & command) {
    m_redo_stack.clear();// don't forget to clear redo stack
    command->Execute();
    m_undo_stack.push(command);
  }
  void Undo() {
    if (m_undo_stack.empty()) return;
    m_undo_stack.top()->Undo();
    m_redo_stack.push(m_undo_stack.top());
    m_undo_stack.pop();
  }
  void Redo() {
    if (m_redo_stack.empty()) return;
    m_redo_stack.top()->Redo();
    m_undo_stack.push(m_redo_stack.top());
    m_redo_stack.pop();
  }
private:
  std::stack<ICommandPtr> m_undo_stack;
  std::stack<ICommandPtr> m_redo_stack;
};

