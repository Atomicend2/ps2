import React, { useState } from 'react';
import { TYRA_DOCS } from '../data/tyraDocs';
import { BookOpen, Copy, Check, Info } from 'lucide-react';

export const ApiReference: React.FC = () => {
  const [activeCategoryIdx, setActiveCategoryIdx] = useState<number>(0);
  const [copiedIdx, setCopiedIdx] = useState<string | null>(null);

  const handleCopyCode = (code: string, id: string) => {
    navigator.clipboard.writeText(code);
    setCopiedIdx(id);
    setTimeout(() => setCopiedIdx(null), 2000);
  };

  return (
    <div className="bg-[#101418] border border-[#22272e] rounded-lg overflow-hidden flex flex-col h-full font-mono text-xs">
      {/* Header */}
      <div className="bg-[#161b22] px-4 py-2.5 border-b border-[#22272e] flex items-center gap-2">
        <BookOpen className="w-4 h-4 text-blue-400" />
        <span className="font-bold text-gray-200 uppercase tracking-wider text-[10px]">
          Tyra Engine API Reference
        </span>
      </div>

      {/* Categories select tab */}
      <div className="flex bg-[#12161b] border-b border-[#22272e] select-none text-[10px]">
        {TYRA_DOCS.map((category, idx) => (
          <button
            key={idx}
            onClick={() => setActiveCategoryIdx(idx)}
            className={`flex-1 py-2 text-center font-bold tracking-tight border-r border-[#22272e] last:border-r-0 transition-colors ${
              activeCategoryIdx === idx ? 'bg-[#101418] text-blue-400 border-t-2 border-t-blue-500' : 'text-gray-500 hover:text-gray-300 hover:bg-[#1a2027]'
            }`}
          >
            {category.title}
          </button>
        ))}
      </div>

      {/* Reference content block */}
      <div className="flex-1 overflow-y-auto p-4 space-y-4">
        <div className="bg-blue-950/10 border border-blue-500/20 rounded p-3 text-[10.5px] text-blue-300 leading-relaxed flex gap-2">
          <Info className="w-4 h-4 text-blue-400 shrink-0 mt-0.5" />
          <p>
            {TYRA_DOCS[activeCategoryIdx].description}
          </p>
        </div>

        <div className="space-y-4">
          {TYRA_DOCS[activeCategoryIdx].snippets.map((snippet, idx) => {
            const uniqueId = `${activeCategoryIdx}-${idx}`;
            const isCopied = copiedIdx === uniqueId;

            return (
              <div key={idx} className="bg-[#0b0d10] border border-[#22272e] rounded overflow-hidden">
                <div className="bg-[#12161b] px-3 py-1.5 border-b border-[#22272e] flex justify-between items-center">
                  <div>
                    <h4 className="font-bold text-gray-200">{snippet.name}</h4>
                    <p className="text-[10px] text-gray-500 font-normal leading-normal">{snippet.description}</p>
                  </div>
                  <button
                    onClick={() => handleCopyCode(snippet.code, uniqueId)}
                    className="p-1 hover:bg-[#2c3541] rounded text-gray-400 hover:text-white transition-colors flex items-center gap-1 text-[9px]"
                  >
                    {isCopied ? (
                      <>
                        <Check className="w-3.5 h-3.5 text-emerald-400" />
                        <span className="text-emerald-400 font-bold">Copied</span>
                      </>
                    ) : (
                      <>
                        <Copy className="w-3.5 h-3.5" />
                        <span>Copy</span>
                      </>
                    )}
                  </button>
                </div>
                <pre className="p-3 bg-[#0d0f12] text-amber-300 font-mono text-[10.5px] overflow-x-auto select-all leading-relaxed max-h-[160px]">
                  <code>{snippet.code}</code>
                </pre>
              </div>
            );
          })}
        </div>
      </div>
    </div>
  );
};
