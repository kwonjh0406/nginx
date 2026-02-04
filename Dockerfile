# 1. Base image (Lightweight Alpine version)
FROM nginx:alpine

# 2. Add custom configuration
# Overwrite the default Nginx config with our own
COPY default.conf /etc/nginx/conf.d/default.conf

# 3. Copy static files
# Move our index.html to the default Nginx public directory
COPY index.html /usr/share/nginx/html/index.html

# 4. Expose port 80
EXPOSE 80

# 5. Start Nginx (This is the default for the nginx image)
CMD ["nginx", "-g", "daemon off;"]
