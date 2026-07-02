import React, { useState, useEffect } from 'react';
import { Copy, Download, Save, Edit, Eye, Terminal } from 'lucide-react';
import { VirtualFile } from '../types';

interface CodeEditorProps {
  file: VirtualFile;
  onUpdateContent: (path: string, content: string) => void;
}

export const CodeEditor: React.FC<CodeEditorProps> = ({ file, onUpdateContent }) => {
  const [editorContent, setEditorContent] = useState(file.content);
  const [isEditing, setIsEditing] = useState(false);
  const [copied, setCopied] = useState(false);
  const [saved, setSaved] = useState(false);

  // Sync state when file changes
  useEffect(() => {
    setEditorContent(file.content);
    setIsEditing(false);
    setSaved(false);
  }, [file]);

  const handleSave = () => {
    onUpdateContent(file.path, editorContent);
    setSaved(true);
    setTimeout(() => setSaved(false), 2000);
  };

  const handleCopy = () => {
    navigator.clipboard.writeText(editorContent);
    setCopied(true);
    setTimeout(() => setCopied(false), 2000);
  };

  const handleDownload = () => {
    const blob = new Blob([editorContent], { type: 'text/plain' });
    const url = URL.createObjectURL(blob);
    const a = document.createElement('a');
    a.href = url;
    a.download = file.name;
    document.body.appendChild(a);
    a.click();
    document.body.removeChild(a);
    URL.revokeObjectURL(url);
  };

  // Basic regex syntax highlighter for aesthetic rendering
  const highlightCode = (code: string, lang: string) => {
    if (!code) return '';

    // Escape HTML first
    let escaped = code
      .replace(/&/g, '&amp;')
      .replace(/</g, '&lt;')
      .replace(/>/g, '&gt;');

    if (lang === 'cpp' || lang === 'hpp') {
      // Directives
      escaped = escaped.replace(/(#include|#define|#ifndef|#endif|#ifndef)/g, '<span class="text-pink-400 font-bold">$1</span>');
      // Keywords
      escaped = escaped.replace(/\b(int|float|double|char|void|class|struct|namespace|public|private|override|const|return|enum|switch|case|default|typename|u32|s32|float&|float\*|const float&)\b/g, '<span class="text-blue-400">$1</span>');
      // Tyra specific types & macros
      escaped = escaped.replace(/\b(TYRA_LOG|Tyra|Engine|Game|EngineOptions|Vmode|Mesh|Texture|Sprite|Button|pads|pad|audio|renderer|beginFrame|endFrame|usePipeline|staticPipeline|isClicked|isPressed)\b/g, '<span class="text-cyan-400">$1</span>');
      // Comments
      escaped = escaped.replace(/(\/\/.*)/g, '<span class="text-gray-500 italic">$1</span>');
      escaped = escaped.replace(/(\/\*[\s\S]*?\*\/)/g, '<span class="text-gray-500 italic">$1</span>');
      // Strings
      escaped = escaped.replace(/(["'].*?["'])/g, '<span class="text-amber-300">$1</span>');
    } else if (lang === 'makefile') {
      // Variables and targets
      escaped = escaped.replace(/^([A-Za-z0-9_]+)\s*=/gm, '<span class="text-cyan-400">$1</span> =');
      escaped = escaped.replace(/^([A-Za-z0-9_.-]+):/gm, '<span class="text-emerald-400 font-bold">$1</span>:');
      // Comments
      escaped = escaped.replace(/(#.*)/g, '<span class="text-gray-500 italic">$1</span>');
      // Makefile directives
      escaped = escaped.replace(/\b(all|clean|\.PHONY|mkdir|rm)\b/g, '<span class="text-pink-400">$1</span>');
    } else if (lang === 'cnf') {
      escaped = escaped.replace(/^([A-Za-z0-9_]+)\s*=/gm, '<span class="text-pink-400">$1</span> =');
      escaped = escaped.replace(/(cdrom0:\\\\?[A-Za-z0-9_./;\\]+)/g, '<span class="text-amber-300">$1</span>');
    } else if (lang === 'txt' || lang === 'dat') {
      escaped = escaped.replace(/\b(ZONE_INIT|SPAWN_ENEMY|SET_CAMERA_TARGET|LOAD_DIALOGUE|PURGE_MEM|VRAM_LOAD|LOAD_NPC|SET_VOW_MOD|TRIGGER_GLITCH)\b/g, '<span class="text-pink-400 font-bold">$1</span>');
      escaped = escaped.replace(/\b(0x[0-9A-Fa-f]+|\b\d+\b)\b/g, '<span class="text-blue-400">$1</span>');
      escaped = escaped.replace(/(["'].*?["'])/g, '<span class="text-amber-300">$1</span>');
      escaped = escaped.replace(/(#.*|\/\/.*)/g, '<span class="text-gray-500 italic">$1</span>');
    }

    return escaped;
  };

  const lineCount = editorContent.split('\n').length;

  return (
    <div className="bg-[#0f1216] h-full flex flex-col font-mono text-xs border border-[#22272e] rounded-lg overflow-hidden shadow-2xl">
      {/* Tab bar header */}
      <div className="flex justify-between items-center bg-[#161b22] px-4 py-2 border-b border-[#22272e]">
        <div className="flex items-center gap-2">
          <Terminal className="w-3.5 h-3.5 text-gray-400" />
          <span className="text-gray-300 font-bold tracking-tight">{file.path}</span>
          <span className="bg-gray-800 text-gray-500 px-1.5 py-0.5 rounded text-[9px] uppercase font-bold tracking-wider">
            {file.language}
          </span>
        </div>

        <div className="flex items-center gap-2.5">
          {/* Editor Mode Toggle */}
          <button
            onClick={() => setIsEditing(!isEditing)}
            className="flex items-center gap-1.5 px-2.5 py-1 rounded bg-[#21262d] text-gray-300 hover:bg-[#30363d] border border-[#30363d] transition-all hover:text-white"
          >
            {isEditing ? (
              <>
                <Eye className="w-3.5 h-3.5" />
                <span>Read-Only View</span>
              </>
            ) : (
              <>
                <Edit className="w-3.5 h-3.5" />
                <span>Edit Source</span>
              </>
            )}
          </button>

          <button
            onClick={handleCopy}
            className="p-1.5 hover:bg-[#21262d] rounded text-gray-400 hover:text-gray-200 transition-colors"
            title="Copy Code"
          >
            <Copy className="w-3.5 h-3.5" />
          </button>

          <button
            onClick={handleDownload}
            className="p-1.5 hover:bg-[#21262d] rounded text-gray-400 hover:text-gray-200 transition-colors"
            title="Download File"
          >
            <Download className="w-3.5 h-3.5" />
          </button>

          {isEditing && (
            <button
              onClick={handleSave}
              className={`flex items-center gap-1.5 px-3 py-1 rounded font-bold transition-all ${
                saved
                  ? 'bg-emerald-600 text-white'
                  : 'bg-blue-600 hover:bg-blue-700 text-white active:scale-95 shadow-md shadow-blue-950'
              }`}
            >
              <Save className="w-3.5 h-3.5" />
              <span>{saved ? 'Saved!' : 'Save'}</span>
            </button>
          )}
        </div>
      </div>

      {/* Editor Body */}
      <div className="flex-1 flex overflow-hidden">
        {/* Line numbers column */}
        <div className="py-4 select-none text-right text-gray-600 bg-[#0d0f12] border-r border-[#21262d] w-12 pr-3 space-y-1 font-mono text-xs leading-5">
          {Array.from({ length: lineCount }).map((_, i) => (
            <div key={i}>{i + 1}</div>
          ))}
        </div>

        {/* Core content area */}
        <div className="flex-1 overflow-auto bg-[#0f1216] relative">
          {copied && (
            <div className="absolute top-4 right-4 bg-gray-900 text-emerald-400 border border-emerald-500/30 px-3 py-1 rounded text-[10px] animate-fade-in shadow-lg">
              Copied to Clipboard!
            </div>
          )}

          {isEditing ? (
            <textarea
              value={editorContent}
              onChange={(e) => setEditorContent(e.target.value)}
              className="w-full h-full bg-[#0f1216] text-gray-200 font-mono text-xs leading-5 p-4 border-0 focus:ring-0 outline-none resize-none align-top whitespace-pre font-normal"
              spellCheck="false"
            />
          ) : (
            <pre className="p-4 m-0 font-mono text-xs leading-5 text-gray-300 align-top whitespace-pre overflow-visible">
              <code
                dangerouslySetInnerHTML={{
                  __html: highlightCode(editorContent, file.language),
                }}
              />
            </pre>
          )}
        </div>
      </div>
    </div>
  );
};
