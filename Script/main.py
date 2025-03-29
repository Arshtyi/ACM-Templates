import os
import shutil
from textwrap import wrap

def main():
    # Get the parent directory of the current script
    current_dir = os.path.dirname(os.path.abspath(__file__))
    parent_dir = os.path.dirname(current_dir)
    
    # Define paths to required directories
    latex_dir = os.path.join(parent_dir, "LaTeX")
    markdown_dir = os.path.join(parent_dir, "Markdown")
    pdfs_dir = os.path.join(parent_dir, "PDFs")
    
    # Create PDFs directory if it doesn't exist
    if not os.path.exists(pdfs_dir):
        os.makedirs(pdfs_dir)
        print(f"已创建目录: {pdfs_dir}")
    
    # Track copied files
    copied_files = []
    
    # Copy PDF files from LaTeX directory
    if os.path.exists(latex_dir):
        for file in os.listdir(latex_dir):
            file_path = os.path.join(latex_dir, file)
            dest_path = os.path.join(pdfs_dir, file)
            
            if os.path.isfile(file_path) and file.lower().endswith('.pdf'):
                try:
                    shutil.copy2(file_path, pdfs_dir)
                    print(f"已复制: {file} (来自LaTeX目录)")
                    copied_files.append(file)
                except Exception as e:
                    print(f"复制 {file} 时出错: {e}")
    else:
        print(f"警告: 未找到LaTeX目录 {latex_dir}")
    
    # Copy PDF files from Markdown subdirectories
    if os.path.exists(markdown_dir):
        for dir_name in os.listdir(markdown_dir):
            dir_path = os.path.join(markdown_dir, dir_name)
            if os.path.isdir(dir_path):
                for file in os.listdir(dir_path):
                    file_path = os.path.join(dir_path, file)
                    dest_path = os.path.join(pdfs_dir, file)
                    
                    if os.path.isfile(file_path) and file.lower().endswith('.pdf'):
                        try:
                            shutil.copy2(file_path, pdfs_dir)
                            print(f"已复制: {file} (来自Markdown/{dir_name}目录)")
                            copied_files.append(file)
                        except Exception as e:
                            print(f"复制 {file} 时出错: {e}")
    else:
        print(f"警告: 未找到Markdown目录 {markdown_dir}")
    
    # Print summary with nice formatting
    border = "=" * 110
    print(border)
    print(f"总共复制了 {len(copied_files)} 个文件")
    print(border)
    
    if copied_files:
        # Sort files alphabetically
        copied_files.sort()
        
        # Get terminal width (fallback to 80 if can't determine)
        try:
            terminal_width = os.get_terminal_size().columns
        except:
            terminal_width = 80
            
        # Calculate max filename length and optimal column width
        max_filename_length = max(len(f) for f in copied_files) if copied_files else 0
        col_width = max_filename_length + 2  # Add spacing between columns
        
        # Calculate number of columns that can fit
        cols = max(1, terminal_width // col_width)
        
        # Calculate rows needed
        rows = (len(copied_files) + cols - 1) // cols
        
        # Print in unix-style columns (files arranged vertically then horizontally)
        for row in range(rows):
            line = ""
            for col in range(cols):
                idx = row + col * rows
                if idx < len(copied_files):
                    line += copied_files[idx].ljust(col_width)
            print(line.rstrip())
    else:
        print("没有文件被复制")
        
    print(border)
    print("操作完成")

if __name__ == "__main__":
    main()