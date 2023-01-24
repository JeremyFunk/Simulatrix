#pragma once
#include "Simulatrix/Core/Core.h"
#include "Command.h"

namespace Simulatrix {
    class CommandStack
    {
    public:
        static void PushCommand(Ref<Command> command);
        static Ref<Command> Undo();
        static Ref<Command> Redo();
        static void Clear();
        static bool CanUndo();
        static bool CanRedo();
        static std::string GetUndoName();
        static std::string GetRedoName();
    private:
        static std::vector<Ref<Command>> s_UndoStack;
        static std::vector<Ref<Command>> s_RedoStack;
    };
}
