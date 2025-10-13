
import csv
import time
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options
from selenium.common.exceptions import TimeoutException, NoSuchElementException
from webdriver_manager.chrome import ChromeDriverManager
import logging

# Configure logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger(__name__)

# credentials
email = "alvaro.davisa@gmail.com"
senha = "LorienLives5@"

playlist_url = "https://www.youtube.com/playlist?list=WL"

# csv columns: ID do vídeo,Carimbo de data/hora da criação do vídeo da playlist
csv_file = "/media/alvaro/MyFiles/Downloads/Takeout/playlists/Vídeos da playlist Watch later.csv"

def setup_driver():
    """Configure and return Chrome WebDriver"""
    chrome_options = Options()
    chrome_options.add_argument("--disable-blink-features=AutomationControlled")
    chrome_options.add_experimental_option("excludeSwitches", ["enable-automation"])
    chrome_options.add_experimental_option('useAutomationExtension', False)
    chrome_options.add_argument("--no-sandbox")
    chrome_options.add_argument("--disable-dev-shm-usage")
    
    # Uncomment the line below if you want to run in headless mode
    # chrome_options.add_argument("--headless")
    
    # Use webdriver-manager to automatically handle ChromeDriver
    service = Service(ChromeDriverManager().install())
    driver = webdriver.Chrome(service=service, options=chrome_options)
    driver.execute_script("Object.defineProperty(navigator, 'webdriver', {get: () => undefined})")
    return driver

def login_youtube(driver, email, password):
    """Login to YouTube"""
    logger.info("Navegando para YouTube...")
    driver.get("https://www.youtube.com")
    
    # Wait for page to load
    time.sleep(3)
    
    # Click sign in button
    try:
        sign_in_button = WebDriverWait(driver, 10).until(
            EC.element_to_be_clickable((By.XPATH, "//*[@id='buttons']/ytd-button-renderer/yt-button-shape"))
        )
        sign_in_button.click()
        logger.info("Clicou no botão de login")
    except TimeoutException:
        logger.error("Não foi possível encontrar o botão de login")
        return False
    
    # Enter email
    try:
        email_input = WebDriverWait(driver, 10).until(
            EC.presence_of_element_located((By.ID, "identifierId"))
        )
        email_input.send_keys(email)
        
        next_button = driver.find_element(By.ID, "identifierNext")
        next_button.click()
        logger.info("Email inserido")
        time.sleep(3)
    except (TimeoutException, NoSuchElementException):
        logger.error("Não foi possível inserir o email")
        return False
    
    # Enter password
    try:
        password_input = WebDriverWait(driver, 10).until(
            EC.element_to_be_clickable((By.XPATH, "//input[@type='password']"))
        )
        password_input.send_keys(password)
        
        password_next = driver.find_element(By.ID, "passwordNext")
        password_next.click()
        logger.info("Senha inserida")
        time.sleep(10)
    except (TimeoutException, NoSuchElementException):
        logger.error("Não foi possível inserir a senha")
        return False
    
    return True

def read_video_ids_from_csv(csv_file_path):
    """Read video IDs from CSV file"""
    video_ids = []
    try:
        with open(csv_file_path, 'r', encoding='utf-8') as file:
            csv_reader = csv.DictReader(file)
            for row in csv_reader:
                video_id = row.get('ID do vídeo', '').strip()
                if video_id:
                    video_ids.append(video_id)
        logger.info(f"Lidos {len(video_ids)} IDs de vídeo do CSV")
    except FileNotFoundError:
        logger.error(f"Arquivo CSV não encontrado: {csv_file_path}")
    except Exception as e:
        logger.error(f"Erro ao ler arquivo CSV: {e}")
    
    return video_ids

def add_video_to_playlist(driver, video_id):
    """Add a single video to playlist using the add video button"""
    try:
        # x1: Click on "adicionar vídeo" button
        add_video_button = WebDriverWait(driver, 10).until(
            EC.element_to_be_clickable((By.XPATH, "//*[@id='button-shape']"))
        )
        add_video_button.click()
        logger.info(f"Clicou em 'adicionar vídeo' para o vídeo {video_id}")
        time.sleep(2)
        
        # x2: Wait for dropdown to appear
        dropdown = WebDriverWait(driver, 10).until(
            EC.presence_of_element_located((By.XPATH, "/html/body/ytd-app/ytd-popup-container/tp-yt-iron-dropdown"))
        )
        logger.info("Dropdown apareceu")
        
        # x3: Insert video ID in the input field
        video_input = WebDriverWait(driver, 10).until(
            EC.element_to_be_clickable((By.XPATH, "//*[@id='yDmH0d']/div[2]/div[2]/div/div/div[2]/div/div/div[2]/div[1]/input[2]"))
        )
        video_input.clear()
        video_input.send_keys(video_id)
        logger.info(f"ID do vídeo {video_id} inserido no input")
        
        # Press Enter
        video_input.send_keys(Keys.RETURN)
        time.sleep(2)
        
        # x4: Select first item
        first_item = WebDriverWait(driver, 10).until(
            EC.element_to_be_clickable((By.XPATH, "//*[@id='yDmH0d']/div[2]/div[3]/div[2]/div[2]/div/div/div[2]/div[2]/div/div[2]/div[1]"))
        )
        first_item.click()
        logger.info("Primeiro item selecionado")
        time.sleep(2)
        
        # x5: Click "adicionar videos" button
        add_videos_button = WebDriverWait(driver, 10).until(
            EC.element_to_be_clickable((By.XPATH, "//*[@id='yDmH0d']/div[2]/div[5]/div/div[3]/button"))
        )
        add_videos_button.click()
        logger.info(f"Vídeo {video_id} adicionado à playlist")
        
        # Wait 10 seconds before next video
        time.sleep(10)
        
        return True
        
    except (TimeoutException, NoSuchElementException) as e:
        logger.error(f"Erro ao adicionar vídeo {video_id}: {e}")
        return False

def main():
    """Main function"""
    if not email or not senha:
        logger.error("Por favor, preencha as credenciais de email e senha")
        return
    
    driver = setup_driver()
    
    try:
        # Login to YouTube
        if not login_youtube(driver, email, senha):
            logger.error("Falha no login")
            return
        
        # Read video IDs from CSV
        video_ids = read_video_ids_from_csv(csv_file)
        if not video_ids:
            logger.error("Nenhum ID de vídeo encontrado no CSV")
            return
        
        # Navigate to playlist
        driver.get(playlist_url)
        time.sleep(3)
        
        # Add each video to playlist
        success_count = 0
        for i, video_id in enumerate(video_ids, 1):
            logger.info(f"Processando vídeo {i}/{len(video_ids)}: {video_id}")
            
            if add_video_to_playlist(driver, video_id):
                success_count += 1
            
            # Note: delay is already included in add_video_to_playlist function
        
        logger.info(f"Processo concluído. {success_count}/{len(video_ids)} vídeos adicionados com sucesso")
        
    except Exception as e:
        logger.error(f"Erro durante a execução: {e}")
    
    finally:
        # Keep browser open for a few seconds before closing
        time.sleep(5)
        driver.quit()

if __name__ == "__main__":
    main()
