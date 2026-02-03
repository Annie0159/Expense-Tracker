# Expense Tracker (C++ / MySQL / Python)

## Overview
**Expense Tracker** is a cross-language expense management system that helps users record and organize spending, generate reports, and forecast future expenses. The application combines a high-performance **C++ core** for business logic, **MySQL** for persistent storage, and **Python** for machine learning–based predictive analytics.

## Features
- **Add & Manage Expenses**
  - Create, edit, and delete expense entries  
  - Store details such as amount, date, category, and notes
- **Categorization**
  - Assign expenses to categories (e.g., Food, Rent, Travel, Utilities)
  - Support category-based filtering and analysis
- **Summaries & Reports**
  - Generate spending summaries by category and time range (daily/weekly/monthly)
  - Produce reports for budgeting and trend analysis
- **Expense Prediction (ML)**
  - Predict **next month’s expenses** using a Python-based machine learning model
  - Uses historical spending patterns to estimate upcoming totals

## Tech Stack
- **Core logic & data handling:** C++  
- **Database management:** MySQL  
- **Predictive analytics:** Python (Machine Learning)

## System Design
The system is organized into three primary components:
1. **C++ Application Layer**
   - Handles user actions (add/update/delete)
   - Validates inputs and applies business rules
   - Queries the database for summaries and report generation
2. **MySQL Database Layer**
   - Stores expense records and categories
   - Enables efficient retrieval for reporting and analytics
3. **Python ML Module**
   - Pulls historical data (via DB queries or exported dataset)
   - Trains/loads a model and generates next-month expense predictions
   - Returns predictions back to the C++ layer (via file/CLI/API integration)

## Typical Workflow
1. User adds and categorizes expenses through the C++ interface  
2. Data is stored and managed in MySQL  
3. Reports and summaries are generated using database queries  
4. Python module analyzes historical data and predicts next month’s expenses  

## Skills Demonstrated
- Cross-language system integration (C++ ↔ MySQL ↔ Python)
- Database schema design and query-based reporting
- Data preprocessing and machine learning forecasting
- Building maintainable, modular application components
