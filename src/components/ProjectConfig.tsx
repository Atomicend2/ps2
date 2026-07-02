import React from 'react';
import { Sliders, Settings2, Info } from 'lucide-react';
import { ProjectConfig as ConfigType } from '../types';

interface ProjectConfigProps {
  config: ConfigType;
  onChangeConfig: (newConfig: ConfigType) => void;
}

export const ProjectConfig: React.FC<ProjectConfigProps> = ({ config, onChangeConfig }) => {
  const handleChange = (key: keyof ConfigType, value: string) => {
    onChangeConfig({
      ...config,
      [key]: value,
    });
  };

  return (
    <div className="bg-[#101418] border border-[#22272e] rounded-lg overflow-hidden flex flex-col h-full font-mono text-xs">
      {/* Header */}
      <div className="bg-[#161b22] px-4 py-2.5 border-b border-[#22272e] flex items-center gap-2">
        <Sliders className="w-4 h-4 text-blue-400" />
        <span className="font-bold text-gray-200 uppercase tracking-wider text-[10px]">
          PS2 Hardware & Build Tweaker
        </span>
      </div>

      <div className="p-4 space-y-4 overflow-y-auto flex-1">
        <div className="bg-[#1a1f26]/40 border border-[#22272e] p-3 rounded space-y-3">
          <h4 className="font-bold text-blue-400 text-[10px] uppercase flex items-center gap-1.5 border-b border-[#22272e] pb-1.5">
            <Settings2 className="w-3.5 h-3.5" /> Target Executable
          </h4>
          
          <div className="space-y-1">
            <label className="text-[10px] text-gray-500 uppercase">Binary ELF Name</label>
            <input
              type="text"
              value={config.elfName}
              onChange={(e) => handleChange('elfName', e.target.value)}
              className="w-full bg-[#0d1117] text-gray-200 border border-[#30363d] rounded px-2.5 py-1.5 outline-none focus:border-blue-500"
            />
          </div>
        </div>

        <div className="space-y-3">
          <h4 className="font-bold text-gray-300 text-[10px] uppercase tracking-wider">Video Mode & Layout</h4>
          
          <div className="grid grid-cols-2 gap-2">
            <div className="space-y-1">
              <label className="text-[9px] text-gray-500 uppercase">Signal Mode</label>
              <select
                value={config.videoMode}
                onChange={(e) => handleChange('videoMode', e.target.value)}
                className="w-full bg-[#0d1117] text-gray-200 border border-[#30363d] rounded px-2 py-1 outline-none"
              >
                <option value="NTSC">NTSC (60Hz / USA/JP)</option>
                <option value="PAL">PAL (50Hz / EU)</option>
              </select>
            </div>

            <div className="space-y-1">
              <label className="text-[9px] text-gray-500 uppercase">Aspect Ratio</label>
              <select
                value={config.aspectRatio}
                onChange={(e) => handleChange('aspectRatio', e.target.value)}
                className="w-full bg-[#0d1117] text-gray-200 border border-[#30363d] rounded px-2 py-1 outline-none"
              >
                <option value="4:3">4:3 Standard</option>
                <option value="16:9">16:9 Widescreen</option>
              </select>
            </div>
          </div>

          <div className="grid grid-cols-2 gap-2">
            <div className="space-y-1">
              <label className="text-[9px] text-gray-500 uppercase">Resolution</label>
              <select
                value={config.resolution}
                onChange={(e) => handleChange('resolution', e.target.value)}
                className="w-full bg-[#0d1117] text-gray-200 border border-[#30363d] rounded px-2 py-1 outline-none"
              >
                <option value="640x448">640x448 (Standard)</option>
                <option value="512x448">512x448 (Retro Scale)</option>
                <option value="640x512">640x512 (PAL Interlaced)</option>
                <option value="320x240">320x240 (Low Res Progressive)</option>
              </select>
            </div>

            <div className="space-y-1">
              <label className="text-[9px] text-gray-500 uppercase">Audio Frequency</label>
              <select
                value={config.audioFrequency}
                onChange={(e) => handleChange('audioFrequency', e.target.value)}
                className="w-full bg-[#0d1117] text-gray-200 border border-[#30363d] rounded px-2 py-1 outline-none"
              >
                <option value="44100">44.1 kHz CD Quality</option>
                <option value="48000">48.0 kHz Studio Quality</option>
                <option value="22050">22.05 kHz Low Bandwidth</option>
              </select>
            </div>
          </div>
        </div>

        <div className="space-y-3">
          <h4 className="font-bold text-gray-300 text-[10px] uppercase tracking-wider">Emotion Engine Compiler Optimization</h4>
          
          <div className="space-y-1">
            <label className="text-[9px] text-gray-500 uppercase">GCC Flag Settings</label>
            <select
              value={config.optimizationLevel}
              onChange={(e) => handleChange('optimizationLevel', e.target.value)}
              className="w-full bg-[#0d1117] text-gray-200 border border-[#30363d] rounded px-2 py-1 outline-none font-mono"
            >
              <option value="O0">-O0 (No optimizations / Easy Debug)</option>
              <option value="O1">-O1 (Basic CPU optimizations)</option>
              <option value="O2">-O2 (Moderate footprint and speed)</option>
              <option value="O3">-O3 (Aggressive performance / Production)</option>
              <option value="Os">-Os (Optimize for binary space constraints)</option>
            </select>
          </div>
        </div>

        <div className="bg-[#141a21]/50 border border-[#22272e] p-3 rounded text-[10px] text-gray-500 leading-relaxed flex gap-2">
          <Info className="w-4 h-4 text-blue-400 shrink-0 mt-0.5" />
          <p>
            Modifying settings automatically synchronizes C++ includes, build macros, and target binaries on the virtual file tree.
          </p>
        </div>
      </div>
    </div>
  );
};
