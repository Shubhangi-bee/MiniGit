import streamlit as st
import subprocess
import os
from pathlib import Path

# =====================================================
# PAGE CONFIG
# =====================================================

st.set_page_config(
    page_title="MiniGit",
    page_icon="📂",
    layout="wide"
)

# =====================================================
# CONSTANTS
# =====================================================

SRC_DIR = Path("../src")
MINIGIT = "./minigit"

# =====================================================
# SESSION STATE
# =====================================================

if "console_output" not in st.session_state:
    st.session_state.console_output = ""

if "selected_upload" not in st.session_state:
    st.session_state.selected_upload = None

if "selected_filename" not in st.session_state:
    st.session_state.selected_filename = ""

if "replace_mode" not in st.session_state:
    st.session_state.replace_mode = False

# =====================================================
# HELPER FUNCTION
# =====================================================

def execute(command):

    result = subprocess.run(
        command,
        capture_output=True,
        text=True,
        cwd=str(SRC_DIR)
    )

    output = ""

    if result.stdout:
        output += result.stdout

    if result.stderr:
        output += result.stderr

    st.session_state.console_output = output

# =====================================================
# REPOSITORY INFO
# =====================================================

def repository_info():

    head = "NULL"
    commits = 0
    staged = 0
    status = "Clean"

    try:
        with open(SRC_DIR / ".minigit" / "HEAD") as file:
            head = file.read().strip()
    except:
        pass

    try:
        commits = len(
            os.listdir(
                SRC_DIR / ".minigit" / "commits"
            )
        )
    except:
        pass

    try:
        staged = len(
            os.listdir(
                SRC_DIR / ".minigit" / "staging"
            )
        )
    except:
        pass

    if staged > 0:
        status = "Staged"

    return head, commits, staged, status

# =====================================================
# SIDEBAR
# =====================================================

with st.sidebar:

    st.title("📂 MiniGit")

    st.markdown("---")

    st.subheader("Features")

    st.success("Initialize")
    st.success("Status")
    st.success("Add File")
    st.success("Commit")
    st.success("View Log")
    st.success("Checkout")

    st.markdown("---")

    st.info(
        """
### MiniGit

Version : **1.0**

Built using

- C++
- Python
- Streamlit

👩‍💻 Developed by

**Shubhangi**
"""
    )

# =====================================================
# TITLE
# =====================================================

st.title("📂 MiniGit")

st.caption(
    "A Simple Git Inspired Version Control System"
)

head, commits, staged, status = repository_info()

if status == "Clean":
    status_display = "🟢 CLEAN"
elif status == "Staged":
    status_display = "🟡 STAGED"
else:
    status_display = "🔴 NOT INITIALIZED"

# =====================================================
# DASHBOARD
# =====================================================

c1, c2, c3, c4 = st.columns(4)

with c1:
    st.metric("📍 HEAD", head)

with c2:
    st.metric("📝 COMMITS", commits)

with c3:
    st.metric("📄 STAGED", staged)

with c4:
    st.metric("✅ STATUS", status_display)

st.divider()

# =====================================================
# REPOSITORY
# =====================================================

col1, col2 = st.columns(2)

with col1:

    st.subheader("Repository")

    if st.button(
        "🚀 Initialize Repository",
        use_container_width=True
    ):
        execute([MINIGIT, "init"])

with col2:

    st.subheader("Status")

    if st.button(
        "📄 Check Status",
        use_container_width=True
    ):
        execute([MINIGIT, "status"])

st.divider()

# =====================================================
# ADD FILE
# =====================================================

st.subheader("📂 Add File")

tab1, tab2 = st.tabs(
    [
        "📄 Repository File",
        "📂 Import New File"
    ]
)

# =====================================================
# Repository File
# =====================================================

with tab1:
    repo_files = sorted(
        [
            file
            for file in os.listdir(SRC_DIR)
            if file.endswith(".txt")
        ]
    )

    if repo_files:

        selected = st.selectbox(
            "Repository Files",
            repo_files
        )

        if st.button(
            "➕ Add File",
            use_container_width=True
        ):

            execute(
                [
                    MINIGIT,
                    "add",
                    selected
                ]
            )

            st.success(
                f"{selected} staged successfully."
            )

    else:

        st.info(
            "No .txt files found."
        )

# =====================================================
# Import New File
# =====================================================

with tab2:

    uploaded = st.file_uploader(
        "Choose a file"
    )

    if uploaded is not None:

        destination = SRC_DIR / uploaded.name

        if destination.exists():

            st.warning(
                "⚠ File already exists."
            )

        else:

            with open(
                destination,
                "wb"
            ) as file:

                file.write(
                    uploaded.getbuffer()
                )

            execute(
                [
                    MINIGIT,
                    "add",
                    uploaded.name
                ]
            )

            st.success(
                "✅ File imported and staged successfully."
            )

st.divider()

# =====================================================
# COMMIT
# =====================================================

st.subheader("📝 Commit")
commit_message = st.text_input(
    "Commit Message",
    placeholder="Example : Fixed login bug"
)

if st.button(
    "✅ Commit Changes",
    use_container_width=True
):

    if commit_message.strip() == "":

        st.warning(
            "Please enter a commit message."
        )

    else:

        execute(
            [
                MINIGIT,
                "commit",
                "-m",
                commit_message
            ]
        )

        st.success(
            "Commit created successfully."
        )

st.divider()

# =====================================================
# COMMIT HISTORY
# =====================================================

st.subheader("📜 Commit History")

if st.button(
    "📖 View Log",
    use_container_width=True
):

    execute(
        [
            MINIGIT,
            "log"
        ]
    )

st.divider()

# =====================================================
# CHECKOUT
# =====================================================

st.subheader("🔄 Checkout Commit")

commit_id = st.number_input(
    "Commit ID",
    min_value=1,
    step=1
)

if st.button(
    "Checkout",
    use_container_width=True
):

    execute(
        [
            MINIGIT,
            "checkout",
            str(commit_id)
        ]
    )

st.divider()

# =====================================================
# CONSOLE
# =====================================================

st.subheader("🖥 Console")

st.caption("💻 Displays the output of every MiniGit command.")

st.text_area(
        "Output",
        value=st.session_state.console_output,
        height=350,
        disabled=True
)
# =====================================================
# FOOTER
# =====================================================

st.markdown(
    """
<div style="text-align:center; color:gray;">

MiniGit v1.0

Built with ❤️ using C++, Python & Streamlit

</div>
""",
unsafe_allow_html=True
)