#!/bin/bash

# TFTP 服务器的 IP 地址
TFTP_SERVER="192.168.13.14"

# 遍历当前目录下的所有文件并逐个传输
for file in *; do
    # 检查是否为文件
    if [[ -f "$file" ]]; then
        echo "正在传输文件: $file"
        tftp -gr "$file" "$TFTP_SERVER"
        
        # 检查传输是否成功
        if [[ $? -ne 0 ]]; then
            echo "文件传输失败: $file"
        else
            echo "文件传输成功: $file"
        fi
    fi
done

echo "所有文件传输完成！"

