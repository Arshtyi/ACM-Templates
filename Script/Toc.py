#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
TOC Generator for ACMTemplates

This script parses a LaTeX TOC file and generates a tree-structured
representation in Markdown format, similar to the Windows 'tree' command output.
"""

import os
import sys
import re

def get_level(line):
    """
    获取行的层级
    
    Args:
        line: TOC文件中的一行
        
    Returns:
        整数表示的层级 (1=section, 2=subsection, 3=subsubsection)
    """
    if "subsubsection" in line:
        return 3
    elif "subsection" in line:
        return 2
    elif "section" in line:
        return 1
    return 0

def extract_section_name(line):
    """
    从TOC行中提取章节名称
    
    Args:
        line: TOC文件中的一行
        
    Returns:
        提取的章节名称
    """
    # 匹配 \numberline {x.y} 和 }{page} 之间的文本
    match = re.search(r'\\numberline\s*{[^}]*}([^}]*)\}\{', line)
    if match:
        return match.group(1).strip()
    return "Unknown Section"

def is_last_at_level(tree, index, level):
    """
    检查节点是否是其级别的最后一个
    
    Args:
        tree: 树结构列表
        index: 当前节点索引
        level: 当前节点级别
        
    Returns:
        布尔值表示是否是最后一个
    """
    for i in range(index + 1, len(tree)):
        if tree[i][0] <= level:  # 找到下一个相同或更高级别的节点
            return tree[i][0] < level  # 如果下一个节点级别更高，则当前节点是最后一个
    return True  # 如果没有后续节点，则当前节点是最后一个

def get_prefix(tree, index):
    """
    生成节点的前缀
    
    Args:
        tree: 树结构列表
        index: 当前节点索引
        
    Returns:
        字符串表示的前缀
    """
    level, _ = tree[index]
    prefix = ""
    
    # 对于每一级，检查是否需要继续画竖线
    for l in range(1, level):
        # 检查当前节点在l级别后面是否还有节点
        has_more = False
        for i in range(index + 1, len(tree)):
            if tree[i][0] <= l:
                has_more = (tree[i][0] == l)
                break
        
        if has_more:
            prefix += "│   "
        else:
            prefix += "    "
    
    # 当前级别是最后一个吗？
    if is_last_at_level(tree, index, level):
        prefix += "└───"
    else:
        prefix += "├───"
    
    return prefix

def main():
    """主函数"""
    try:
        # 获取路径
        script_dir = os.path.dirname(os.path.abspath(__file__))
        project_root = os.path.dirname(script_dir)
        
        toc_file_path = os.path.join(project_root, "LaTeX", "ACMTemplates.toc")
        output_file_path = os.path.join(project_root, "TOC.md")
        
        # 检查文件是否存在
        if not os.path.exists(toc_file_path):
            print(f"Error: TOC file not found: {toc_file_path}")
            return 1
        
        # 读取TOC文件
        with open(toc_file_path, 'r', encoding='utf-8') as f:
            lines = [line.strip() for line in f if line.strip() and not line.startswith('//')]
        
        # 构建树 - 同时提取章节名
        tree = []
        for line in lines:
            level = get_level(line)
            if level > 0:
                section_name = extract_section_name(line)
                tree.append((level, section_name))
        
        if not tree:
            print("Warning: No valid entries found in TOC file.")
            return 1
        
        # 生成树形文本
        result = ["```", "ACMTemplates"]
        
        for i in range(len(tree)):
            prefix = get_prefix(tree, i)
            level, section_name = tree[i]
            result.append(f"{prefix}{section_name}")
        
        result.append("```")
        
        # 写入输出文件
        with open(output_file_path, 'w', encoding='utf-8') as f:
            f.write("\n".join(result))
        
        print(f"TOC tree generated successfully: {output_file_path}")
        return 0
        
    except Exception as e:
        print(f"Error: {e}")
        return 1

if __name__ == "__main__":
    sys.exit(main())