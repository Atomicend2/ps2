import { useState, useEffect } from 'react';
import { FileExplorer } from './components/FileExplorer';
import { CodeEditor } from './components/CodeEditor';
import { Simulator } from './components/Simulator';
import { ApiReference } from './components/ApiReference';
import { ProjectConfig } from './components/ProjectConfig';
import { INITIAL_FILES } from './data/tyraDocs';
import { VirtualFile, ProjectConfig as ConfigType } from './types';
import { Layers, HelpCircle, Laptop } from 'lucide-react';

export default function App() {
  const [files, setFiles] = useState<VirtualFile[]>(INITIAL_FILES);
  const [activeFile, setActiveFile] = useState<VirtualFile>(INITIAL_FILES[2]); // Default to main.cpp
  const [rightPanelTab, setRightPanelTab] = useState<'docs' | 'config'>('config');

  const [config, setConfig] = useState<ConfigType>({
    elfName: 'SEVENTH_VOW.ELF',
    videoMode: 'NTSC',
    resolution: '640x448',
    aspectRatio: '4:3',
    audioFrequency: '44100',
    optimizationLevel: 'O3',
  });

  // Automated config sync engine
  const handleConfigChange = (newConfig: ConfigType) => {
    setConfig(newConfig);

    setFiles((prevFiles) => {
      const synced = prevFiles.map((file) => {
        let content = file.content;

        if (file.name === 'SYSTEM.CNF') {
          content = `BOOT2 = cdrom0:\\${newConfig.elfName.toUpperCase()};1\nVER = 1.00\nVMODE = ${newConfig.videoMode}\n`;
        }

        if (file.name === 'Makefile') {
          // Replace output ELF name
          content = content.replace(/^EE_BIN = .+/m, `EE_BIN = ${newConfig.elfName}`);
          // Replace compiler optimization level
          content = content.replace(/-O[0-3|s]/g, `-${newConfig.optimizationLevel}`);
        }

        if (file.name === 'main.cpp') {
          // Replace video mode
          content = content.replace(/options\.vmode = Tyra::Vmode::.+;/g, `options.vmode = Tyra::Vmode::${newConfig.videoMode};`);
          // Replace width and height from resolution string
          const [w, h] = newConfig.resolution.split('x');
          content = content.replace(/options\.width = \d+;/g, `options.width = ${w};`);
          content = content.replace(/options\.height = \d+;/g, `options.height = ${h};`);
          // Replace sound sampling rate
          content = content.replace(/options\.audio_frequency = \d+;/g, `options.audio_frequency = ${newConfig.audioFrequency};`);
        }

        return {
          ...file,
          content,
        };
      });

      // Also update currently active file view if it was modified
      const updatedActiveFile = synced.find((f) => f.path === activeFile.path);
      if (updatedActiveFile) {
        setActiveFile(updatedActiveFile);
      }

      return synced;
    });
  };

  const handleSelectFile = (file: VirtualFile) => {
    setActiveFile(file);
  };

  const handleUpdateFileContent = (path: string, newContent: string) => {
    setFiles((prev) =>
      prev.map((f) => (f.path === path ? { ...f, content: newContent } : f))
    );
    // Sync current active file state
    if (activeFile.path === path) {
      setActiveFile((prev) => ({ ...prev, content: newContent }));
    }
  };

  const handleCreateFile = (name: string, content: string) => {
    const isHeader = name.endsWith('.hpp');
    const path = `src/${name}`;
    const newFile: VirtualFile = {
      name,
      path,
      content,
      language: isHeader ? 'hpp' : 'cpp',
    };
    setFiles((prev) => [...prev, newFile]);
    setActiveFile(newFile);
  };

  const handleDeleteFile = (path: string) => {
    setFiles((prev) => prev.filter((f) => f.path !== path));
    if (activeFile.path === path) {
      setActiveFile(files[2]); // Fallback to main.cpp
    }
  };

  return (
    <div className="min-h-screen bg-[#07090c] text-gray-300 flex flex-col font-sans select-none antialiased">
      {/* Top Navigation / Status Header */}
      <header className="bg-[#0f1216] border-b border-[#22272e] py-3 px-6 flex flex-col md:flex-row justify-between items-center gap-4">
        <div className="flex items-center gap-3">
          <div className="relative">
            <div className="w-8 h-8 rounded-lg bg-blue-600 flex items-center justify-center text-white font-black font-mono tracking-tighter text-sm shadow-md shadow-blue-950">
              PS2
            </div>
            <span className="absolute -top-1 -right-1 flex h-2.5 w-2.5">
              <span className="animate-ping absolute inline-flex h-full w-full rounded-full bg-blue-400 opacity-75" />
              <span className="relative inline-flex rounded-full h-2.5 w-2.5 bg-blue-500" />
            </span>
          </div>
          <div>
            <div className="flex items-center gap-2">
              <h1 className="font-bold text-gray-100 text-sm tracking-wide uppercase font-mono">
                The Seventh Vow
              </h1>
              <span className="text-[10px] bg-[#1e232b] text-gray-400 px-2 py-0.5 rounded font-mono border border-[#2b323c]">
                PS2 Tyra Dev Environment
              </span>
            </div>
            <p className="text-[10px] text-gray-500 font-mono">
              Emotional Engine Toolchain Integration & Live C++ Assembler Workspace
            </p>
          </div>
        </div>

        <div className="flex items-center gap-4 text-xs font-mono">
          <div className="flex items-center gap-1.5 text-gray-500">
            <Laptop className="w-4 h-4 text-blue-500" />
            <span>Devkit Status:</span>
            <span className="text-emerald-400 font-bold uppercase text-[10px]">Connected (DTL-T10000)</span>
          </div>
          <div className="bg-[#161b22] px-3 py-1 rounded border border-[#22272e] flex items-center gap-1">
            <span className="w-1.5 h-1.5 rounded-full bg-emerald-500 animate-pulse" />
            <span className="text-gray-400 text-[10px] uppercase">IOP Stream: Active</span>
          </div>
        </div>
      </header>

      {/* Main Core Layout Dashboard */}
      <main className="flex-1 grid grid-cols-1 lg:grid-cols-12 gap-4 p-4 min-h-0">
        {/* Left Side: Workspace File Explorer */}
        <div className="lg:col-span-3 h-[250px] lg:h-auto min-h-0">
          <FileExplorer
            files={files}
            activeFile={activeFile}
            onSelectFile={handleSelectFile}
            onCreateFile={handleCreateFile}
            onDeleteFile={handleDeleteFile}
          />
        </div>

        {/* Center Section: Live Code Editor & Compiler Terminal Console */}
        <div className="lg:col-span-6 flex flex-col gap-4 min-h-0">
          {/* Code Editor */}
          <div className="flex-1 min-h-[350px]">
            <CodeEditor file={activeFile} onUpdateContent={handleUpdateFileContent} />
          </div>

          {/* Simulator Console */}
          <div className="shrink-0">
            <Simulator config={config} onCompilationStart={() => {}} />
          </div>
        </div>

        {/* Right Section: SDK Configurer & API Documentation Reference Panel */}
        <div className="lg:col-span-3 flex flex-col h-[400px] lg:h-auto min-h-0">
          <div className="bg-[#101418] border border-[#22272e] rounded-lg overflow-hidden flex flex-col h-full">
            {/* Tab selector */}
            <div className="flex border-b border-[#22272e] bg-[#161b22] select-none text-[10px] font-mono">
              <button
                onClick={() => setRightPanelTab('config')}
                className={`flex-1 py-3 text-center font-bold tracking-wider uppercase flex items-center justify-center gap-1.5 transition-all ${
                  rightPanelTab === 'config'
                    ? 'bg-[#101418] text-blue-400 border-t-2 border-t-blue-500'
                    : 'text-gray-500 hover:text-gray-300 hover:bg-[#1a2027]'
                }`}
              >
                <Layers className="w-3.5 h-3.5" />
                <span>Build Settings</span>
              </button>
              <button
                onClick={() => setRightPanelTab('docs')}
                className={`flex-1 py-3 text-center font-bold tracking-wider uppercase flex items-center justify-center gap-1.5 transition-all ${
                  rightPanelTab === 'docs'
                    ? 'bg-[#101418] text-blue-400 border-t-2 border-t-blue-500'
                    : 'text-gray-500 hover:text-gray-300 hover:bg-[#1a2027]'
                }`}
              >
                <HelpCircle className="w-3.5 h-3.5" />
                <span>Engine Guide</span>
              </button>
            </div>

            {/* Tab panels */}
            <div className="flex-1 overflow-hidden min-h-0">
              {rightPanelTab === 'config' ? (
                <ProjectConfig config={config} onChangeConfig={handleConfigChange} />
              ) : (
                <ApiReference />
              )}
            </div>
          </div>
        </div>
      </main>

      {/* Footer System Tray */}
      <footer className="bg-[#090b0e] py-1.5 px-6 border-t border-[#1e232a] text-[10px] text-gray-600 font-mono flex flex-col sm:flex-row justify-between items-center gap-2">
        <p>© 2026 'The Seventh Vow' PS2 RPG Dev Workspace. Powered by Tyra Open-Source Engine.</p>
        <div className="flex items-center gap-4">
          <p>MIPS IV (R5900) Emotion Engine core running at 294.912 MHz</p>
          <div className="h-3 w-px bg-gray-800" />
          <p>Graphics Synthesizer running at 147.456 MHz</p>
        </div>
      </footer>
    </div>
  );
}
