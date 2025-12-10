🔐 Secure Authentication Module for Operating Systems

A lightweight, extensible, and secure authentication system designed to enhance traditional OS login by adding Multi-Factor Authentication (MFA), strong hashing, and protection against common vulnerabilities such as buffer overflows, insecure storage, and logic bypasses.

This module simulates a secure OS login flow using Python, and can optionally integrate with Linux PAM for real-world authentication enforcement.

⭐ Key Features
✅ Multi-Factor Authentication (Time-Based OTP)

Uses TOTP (Time-based One-Time Passwords) via Google Authenticator or similar apps.

Each user has a unique 32-character Base32 MFA secret.

OTPs refresh every 30 seconds.

✅ Secure Password Handling

Passwords are never stored in plain text.

Hashed using bcrypt with auto-generated salts.

Prevents brute-force, rainbow tables, and replay attacks.

✅ JSON-Based User Database

Encrypted-like structure using hashed passwords & secrets.

Easy to manage for academic demonstration.

✅ Terminal Login Simulation

The custom login.py implements:

Username verification

Password authentication

OTP verification

Shell access upon success

✅ Optional PAM Integration (Advanced)

For real Linux use, the project includes:

pam_secure_mfa.so

Instructions to integrate with /etc/pam.d/sudo or /etc/pam.d/login

Safety mechanisms to avoid system lockout

📁 Project Structure
Secure_auth_project/
│
├── login.py             # Main login interface
├── users.json           # User database
│
├── mfa_backend.py       # Core OTP verification logic
├── mfa_admin.py         # Tool to register/reset users
├── mfa_verify.py        # Standalone verifier for PAM
│
├── pam_secure_mfa.c     # C implementation for PAM module
├── pam_secure_mfa.so    # Compiled shared library for PAM
│
├── requirements.txt     # Python dependencies
└── README.md            # Documentation (this file)

🛠 Installation & Setup
1. Install Dependencies
pip install bcrypt pyotp

2. Initialize User Database
python3 mfa_admin.py


Options available:

View users

Enroll new user

Reset user

3. Generate MFA Secret

Automatically generated when enrolling user.
Scan using Google Authenticator.

4. Run Login Simulation
python3 login.py

🔑 How Authentication Works
Step 1 — Username Check

System verifies if the user exists in users.json.

Step 2 — Password Verification

Entered password → hashed using bcrypt

Compared with stored hash securely

Step 3 — OTP Verification

User scans QR code (MFA secret) in authenticator app

Script validates the 6-digit OTP with TOTP algorithm

Step 4 — Secure Shell

On success, user enters a restricted simulated OS shell.

🔐 Security Enhancements
1️⃣ Strong Hashing (bcrypt)

Built-in salt generation

Slow-by-design → resistant to brute force

2️⃣ Time-based 2FA

Eliminates password-only attack vectors

Prevents credential stuffing, phishing, replay

3️⃣ Buffer Overflow Protection

In the PAM version:

Controlled input sizes

Safe C library functions

Bound-checked buffers

4️⃣ Trapdoor Prevention

No hardcoded secrets

No hidden bypass codes

Code fully auditable

5️⃣ Failsafe Lockout Mechanisms

If PAM breaks:

Root shell recovery guide included

Backups of /etc/pam.d/* created automatically

🧪 Testing Instructions
Test OTP Verification
python3 mfa_verify.py <username> <otp>

Test Login Simulation
python3 login.py

If Using PAM:
sudo -k
sudo ls


→ Should prompt for OTP before password.

⚠️ Safety Notes

Never apply PAM module on a real system without backups.

A misconfigured PAM module can lock you out.

Use VM snapshots if possible.

🚀 Future Improvements

Support for backup codes

Push-based MFA (Firebase, Authy)

GUI admin dashboard

Encrypted user database (AES-256)

Honeypot login attempt logging

Rate-limiting brute-force protection

Full system-wide PAM deployment

📜 License

This project is intended for educational and research purposes only.

🧑‍💻 Author

Sumit Kumar
Taran Thakur
Rooban
