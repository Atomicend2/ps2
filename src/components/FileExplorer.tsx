import React, { useState } from 'react';
import { Folder, FileCode, Play, Plus, Trash2, Check, FileText } from 'lucide-react';
import { VirtualFile } from '../types';

interface FileExplorerProps {
  files: VirtualFile[];
  activeFile: VirtualFile;
  onSelectFile: (file: VirtualFile) => void;
  onCreateFile: (name: string, content: string) => void;
  onDeleteFile: (path: string) => void;
}

export const FileExplorer: React.FC<FileExplorerProps> = ({
  files,
  activeFile,
  onSelectFile,
  onCreateFile,
  onDeleteFile,
}) => {
  const [isOpen, setIsOpen] = useState(true);
  const [newFileName, setNewFileName] = useState('');
  const [isCreating, setIsCreating] = useState(false);
  const [templateType, setTemplateType] = useState<'class' | 'empty'>('class');

  const handleCreate = (e: React.FormEvent) => {
    e.preventDefault();
    if (!newFileName.trim()) return;

    let finalName = newFileName.trim();
    if (!finalName.endsWith('.cpp') && !finalName.endsWith('.hpp')) {
      finalName += '.cpp';
    }

    const baseName = finalName.replace(/\.(cpp|hpp)$/, '');
    let fileContent = '';

    if (templateType === 'class') {
      if (finalName.endsWith('.hpp')) {
        fileContent = `/**
 * @file ${finalName}
 * @brief Class definition for ${baseName}
 */

#ifndef SEVENTH_VOW_${baseName.toUpperCase()}_HPP
#define SEVENTH_VOW_${baseName.toUpperCase()}_HPP

#include <tyra>

namespace TheSeventhVow {

class ${baseName} {
public:
    ${baseName}(Tyra::Engine* engine);
    ~${baseName}();

    void init();
    void update(float deltaTime);
    void render();

private:
    Tyra::Engine* engine;
};

} // namespace TheSeventhVow

#endif // SEVENTH_VOW_${baseName.toUpperCase()}_HPP
`;
      } else {
        fileContent = `/**
 * @file ${finalName}
 * @brief Class implementation for ${baseName}
 */

#include "${baseName}.hpp"

namespace TheSeventhVow {

${baseName}::${baseName}(Tyra::Engine* t_engine) : engine(t_engine) {
    // Constructor logic
}

${baseName}::~${baseName}() {
    // Destructor logic
}

void ${baseName}::init() {
    TYRA_LOG("${baseName} initialized.");
}

void ${baseName}::update(float deltaTime) {
    // Update logic per frame
}

void ${baseName}::render() {
    // Render pipeline triggers
}

} // namespace TheSeventhVow
`;
      }
    } else {
      fileContent = `// Empty source file: ${finalName}\n`;
    }

    onCreateFile(finalName, fileContent);
    setNewFileName('');
    setIsCreating(false);
  };

  const getFileIcon = (file: VirtualFile) => {
    switch (file.language) {
      case 'makefile':
        return <FileText className="w-4 h-4 text-amber-500" />;
      case 'cnf':
        return <FileText className="w-4 h-4 text-emerald-400" />;
      case 'hpp':
        return <FileCode className="w-4 h-4 text-cyan-400" />;
      default:
        return <FileCode className="w-4 h-4 text-blue-400" />;
    }
  };

  // Group files by root and src/ folder
  const rootFiles = files.filter(f => !f.path.includes('/'));
  const srcFiles = files.filter(f => f.path.startsWith('src/'));

  return (
    <div className="bg-[#15191e] border-r border-[#262c35] h-full flex flex-col font-mono text-xs">
      <div className="p-3 border-b border-[#262c35] flex justify-between items-center bg-[#1c222a]">
        <span className="font-bold text-gray-300 tracking-wider flex items-center gap-1.5 uppercase text-[10px]">
          <Folder className="w-3.5 h-3.5 text-blue-400" /> Workspace [PS2]
        </span>
        <button
          onClick={() => setIsCreating(!isCreating)}
          className="p-1 hover:bg-[#2c3541] rounded text-blue-400 hover:text-white transition-colors"
          title="Add C++ Source File"
        >
          <Plus className="w-4 h-4" />
        </button>
      </div>

      {isCreating && (
        <form onSubmit={handleCreate} className="p-3 border-b border-[#262c35] bg-[#1a2027] space-y-2">
          <input
            type="text"
            placeholder="player.cpp"
            value={newFileName}
            onChange={(e) => setNewFileName(e.target.value)}
            className="w-full bg-[#0d1117] text-gray-200 border border-[#30363d] rounded px-2 py-1 outline-none focus:border-blue-500 text-xs"
            autoFocus
          />
          <div className="flex justify-between items-center">
            <span className="text-[10px] text-gray-400">Template:</span>
            <div className="flex gap-2">
              <button
                type="button"
                onClick={() => setTemplateType('class')}
                className={`px-1.5 py-0.5 rounded text-[10px] ${templateType === 'class' ? 'bg-blue-600 text-white' : 'bg-[#21262d] text-gray-400'}`}
              >
                C++ Class
              </button>
              <button
                type="button"
                onClick={() => setTemplateType('empty')}
                className={`px-1.5 py-0.5 rounded text-[10px] ${templateType === 'empty' ? 'bg-blue-600 text-white' : 'bg-[#21262d] text-gray-400'}`}
              >
                Blank
              </button>
            </div>
          </div>
          <div className="flex gap-2 justify-end pt-1">
            <button
              type="button"
              onClick={() => setIsCreating(false)}
              className="px-2 py-1 rounded text-[10px] bg-transparent hover:bg-gray-800 text-gray-400"
            >
              Cancel
            </button>
            <button
              type="submit"
              className="px-2 py-1 rounded text-[10px] bg-blue-600 hover:bg-blue-700 text-white flex items-center gap-1"
            >
              <Check className="w-3 h-3" /> Create
            </button>
          </div>
        </form>
      )}

      <div className="flex-1 overflow-y-auto p-2 space-y-2 select-none">
        {/* Project root workspace folder */}
        <div className="space-y-1">
          <div className="flex items-center gap-1.5 text-gray-400 px-1 py-1">
            <Folder className="w-3.5 h-3.5 text-blue-500 fill-blue-500/10" />
            <span className="font-semibold text-gray-300">ps2-project</span>
          </div>

          <div className="pl-4 space-y-1">
            {/* Root Files inside folder */}
            {rootFiles.map(file => {
              const isActive = activeFile.path === file.path;
              return (
                <div
                  key={file.path}
                  onClick={() => onSelectFile(file)}
                  className={`group flex items-center justify-between px-2 py-1 rounded cursor-pointer transition-all ${
                    isActive ? 'bg-[#242d38] text-blue-400 border-l-2 border-blue-500' : 'text-gray-400 hover:bg-[#1a2027] hover:text-gray-200'
                  }`}
                >
                  <div className="flex items-center gap-1.5 overflow-hidden">
                    {getFileIcon(file)}
                    <span className="truncate">{file.name}</span>
                  </div>
                </div>
              );
            })}

            {/* Sub-folder: src */}
            <div className="space-y-1 pt-1">
              <div className="flex items-center gap-1.5 text-gray-400 px-1 py-0.5">
                <Folder className="w-3.5 h-3.5 text-sky-500 fill-sky-500/10" />
                <span className="text-gray-400 font-medium">src</span>
              </div>

              <div className="pl-4 space-y-1">
                {srcFiles.map(file => {
                  const isActive = activeFile.path === file.path;
                  return (
                    <div
                      key={file.path}
                      onClick={() => onSelectFile(file)}
                      className={`group flex items-center justify-between px-2 py-1 rounded cursor-pointer transition-all ${
                        isActive ? 'bg-[#242d38] text-blue-400 border-l-2 border-blue-500' : 'text-gray-400 hover:bg-[#1a2027] hover:text-gray-200'
                      }`}
                    >
                      <div className="flex items-center gap-1.5 overflow-hidden">
                        {getFileIcon(file)}
                        <span className="truncate">{file.name}</span>
                      </div>

                      {/* Do not allow deleting main.cpp or game files since they are core requirements */}
                      {!['main.cpp', 'game.hpp', 'game.cpp'].includes(file.name) && (
                        <button
                          onClick={(e) => {
                            e.stopPropagation();
                            onDeleteFile(file.path);
                          }}
                          className="opacity-0 group-hover:opacity-100 p-0.5 hover:text-red-400 hover:bg-red-500/10 rounded transition-all"
                          title="Delete File"
                        >
                          <Trash2 className="w-3 h-3" />
                        </button>
                      )}
                    </div>
                  );
                })}
              </div>
            </div>
          </div>
        </div>
      </div>

      <div className="p-3 border-t border-[#262c35] bg-[#0d1117]/80 text-[10px] text-gray-500 space-y-1">
        <p className="flex justify-between"><span>Toolchain:</span> <span className="text-gray-400">GCC 3.2.2 (mips)</span></p>
        <p className="flex justify-between"><span>OS Runtime:</span> <span className="text-gray-400">PS2 BIOS v1.00</span></p>
        <p className="flex justify-between"><span>Active Target:</span> <span className="text-blue-400 font-bold font-mono">SEVENTH_VOW.ELF</span></p>
      </div>
    </div>
  );
};
