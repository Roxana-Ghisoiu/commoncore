#!/usr/bin/env python3
import os
import cgi
import json
from datetime import datetime, timedelta

def get_cookie_value(cookie_name):
    """Get cookie value from HTTP_COOKIE environment variable"""
    cookies = os.environ.get('HTTP_COOKIE', '')
    for cookie in cookies.split(';'):
        cookie = cookie.strip()
        if cookie.startswith(cookie_name + '='):
            return cookie.split('=', 1)[1]
    return None

def set_cookie_header(cookie_name, cookie_value, days=7):
    """Generate Set-Cookie header"""
    expires = datetime.now() + timedelta(days=days)
    expires_str = expires.strftime('%a, %d %b %Y %H:%M:%S GMT')
    return f"Set-Cookie: {cookie_name}={cookie_value}; expires={expires_str}; path=/; HttpOnly"

def main():
    # Get request method
    method = os.environ.get('REQUEST_METHOD', 'GET')
    
    print("Content-Type: application/json")
    print()
    
    if method == 'GET':
        # Return current cookies
        cookies = {}
        cookie_string = os.environ.get('HTTP_COOKIE', '')
        for cookie in cookie_string.split(';'):
            cookie = cookie.strip()
            if '=' in cookie:
                name, value = cookie.split('=', 1)
                cookies[name] = value
        
        response = {
            'status': 'success',
            'cookies': cookies,
            'session_id': get_cookie_value('sessionid'),
            'timestamp': datetime.now().isoformat()
        }
        print(json.dumps(response))
    
    elif method == 'POST':
        # Handle POST request to set cookies
        form = cgi.FieldStorage()
        action = form.getvalue('action', '')
        
        if action == 'set_cookie':
            name = form.getvalue('name', '')
            value = form.getvalue('value', '')
            days = int(form.getvalue('days', '7'))
            
            if name and value:
                print(set_cookie_header(name, value, days))
                print()
                response = {
                    'status': 'success',
                    'message': f'Cookie {name} set successfully',
                    'cookie_name': name,
                    'cookie_value': value
                }
                print(json.dumps(response))
            else:
                response = {
                    'status': 'error',
                    'message': 'Cookie name and value required'
                }
                print(json.dumps(response))
        
        elif action == 'clear_cookies':
            # Clear all cookies by setting them to expire
            cookie_string = os.environ.get('HTTP_COOKIE', '')
            for cookie in cookie_string.split(';'):
                cookie = cookie.strip()
                if '=' in cookie:
                    name = cookie.split('=', 1)[0]
                    print(f"Set-Cookie: {name}=; expires=Thu, 01 Jan 1970 00:00:00 GMT; path=/")
            
            print()
            response = {
                'status': 'success',
                'message': 'All cookies cleared'
            }
            print(json.dumps(response))
        
        else:
            response = {
                'status': 'error',
                'message': 'Invalid action'
            }
            print(json.dumps(response))
    
    else:
        response = {
            'status': 'error',
            'message': 'Method not allowed'
        }
        print(json.dumps(response))

if __name__ == '__main__':
    main()
