#!/bin/bash
# 1. 변수 설정 (본인의 환경에 맞게 수정)
REGION="ap-northeast-1"
ACCOUNT_ID="036333380579"  # 본인의 AWS 계정 ID
ECR_REPO="kwonjh0406/nginx"
S3_BUCKET="kwonjh0406-s3"

# 2. 필요한 디렉토리 생성
mkdir -p /home/ec2-user/app/html

# 3. S3에서 최신 설정 및 자산 가져오기
aws s3 cp s3://${S3_BUCKET}/config/default.conf /home/ec2-user/app/default.conf
aws s3 cp s3://${S3_BUCKET}/html/index.html /home/ec2-user/app/html/index.html

# 4. ECR 로그인
aws ecr get-login-password --region ${REGION} | docker login --username AWS --password-stdin ${ACCOUNT_ID}.dkr.ecr.${REGION}.amazonaws.com

# 5. 최신 이미지 Pull (latest 태그 기준)
docker pull ${ACCOUNT_ID}.dkr.ecr.${REGION}.amazonaws.com/${ECR_REPO}:latest

# 6. 컨테이너 실행
docker run -d --name nginx-server -p 80:80 \
  -v /home/ec2-user/app/default.conf:/etc/nginx/conf.d/default.conf \
  -v /home/ec2-user/app/html:/usr/share/nginx/html \
  ${ACCOUNT_ID}.dkr.ecr.${REGION}.amazonaws.com/${ECR_REPO}:latest