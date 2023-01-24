#include "CommandStack.h"

namespace Simulatrix {
    std::vector<Ref<Command>> CommandStack::s_UndoStack = std::vector<Ref<Command>>();
    std::vector<Ref<Command>> CommandStack::s_RedoStack = std::vector<Ref<Command>>();

    void CommandStack::PushCommand(Ref<Command> command) {
        s_UndoStack.push_back(command);
        s_RedoStack.clear();
    }

    Ref<Command> CommandStack::Undo() {
        if (s_UndoStack.size() >= 0) {
            auto c = s_UndoStack.back();
            s_UndoStack.pop_back();
            c->Undo();
            s_RedoStack.push_back(c);
            return c;
        }
        return nullptr;
    }

    Ref<Command> CommandStack::Redo() {

        if (s_UndoStack.size() >= 0) {
            auto c = s_RedoStack.back();
            s_RedoStack.pop_back();
            c->Redo();
            s_UndoStack.push_back(c);
            return c;
        }
        return nullptr;
    }

    void CommandStack::Clear() {
        s_RedoStack.clear();
        s_UndoStack.clear();
    }

    bool CommandStack::CanUndo() {
        return s_UndoStack.size() > 0;
    }

    bool CommandStack::CanRedo() {
        return s_RedoStack.size() > 0;
    }

    std::string CommandStack::GetUndoName() {
        if (s_UndoStack.size() > 0)
            return s_UndoStack.back()->GetName();
        return "";
    }

    std::string CommandStack::GetRedoName() {
        if(s_RedoStack.size() > 0)
            return s_RedoStack.back()->GetName();
        return "";
    }
}